<?php

/**
 * @file
 * theme functions for Comment Easy Reply module.
 */

/**
 * Returns HTML for the module's status report.
 *
 * @param array $variables
 *   An associative array containing:
 *   - comment_easy_reply_node_types: An array of node types with Comment Easy
 *     Reply enabled on.
 *
 * @ingroup themeable
 */
function theme_comment_easy_reply_status_report_page($variables) {
  $rows = array();
  $headers = array(
    'Node type',
    'Current status',
    'Default settings overrided',
    'Settings details',
    'Actions');
  $node_types = node_type_get_names();
  foreach ($node_types as $node_type => $label) {
    $override = '';
    $links = array();
    if (in_array($node_type, $variables['comment_easy_reply_node_types'])) {
      $title = t('OK');
      $class = 'ok';
      $active = '<strong>' . t('enabled') . '</strong>';
      if (_comment_easy_reply_is_node_type_override_active($node_type)) {
        $override = t('Node type specific settings used.');
      }
      else {
        $override = t('Default settings used.');
        $override .= '<br />(' . l(t('Override default settings'), 'admin/structure/types/manage/' . $node_type) . ')';
      }
      $links[] = l(t('Disable'), 'admin/config/content/comment-easy-reply/status', array('query' => array('disable' => $node_type)));
      $links[] = l(t('Edit'), 'admin/structure/types/manage/' . $node_type);
    }
    else {
      $title = t('Warning');
      $class = 'warning';
      $active = t('disabled');
      $links[] = l(t('Enable'), 'admin/config/content/comment-easy-reply/status', array('query' => array('enable' => $node_type)));
    }
    $row = array(
      array(
        'data' => $label,
      ),
      array(
        'data' => $active,
      ),
      array(
        'data' => $override,
      ),
      array(
        'data' => theme('comment_easy_reply_node_type_settings_report', array('node_type' => $node_type)),
      ),
      array(
        'data' => theme('item_list', array('items' => $links)),
      ),
    );
    $rows[] = array('data' => $row, 'class' => array($class));
  }
  return theme('table', array(
    'rows' => $rows,
    'sticky' => FALSE,
    'attributes' => array('class' => array('system-status-report')),
    'header' => $headers,
  ));
}

/**
 * Returns HTML for a node type specific settings configuration.
 *
 * @param array $variables
 *   An associative array containing:
 *   - node_type: The node type machine name.
 */
function theme_comment_easy_reply_node_type_settings_report($variables) {
  $settings = array();
  if (!_comment_easy_reply_is_node_type_active($variables['node_type'])) {
    return '';
  }
  $names = array(
    'comment_easy_reply_reply_from_numlink',
    'comment_easy_reply_replytip_activated',
    'comment_easy_reply_fragment_activated',
    'comment_easy_reply_link_mode',
    'comment_easy_reply_filter',
    'comment_easy_reply_replytip_text',
    'comment_easy_reply_referrertip_text',
    'comment_easy_reply_fragment_text',
  );
  if (module_exists('quote')) {
    $names[] = 'comment_easy_reply_quote_tooltip';
  }
  foreach ($names as $name) {
    $value = _comment_easy_reply_get_settings_value($name, $variables['node_type']);
    $label = '';
    switch ($name) {
      case 'comment_easy_reply_reply_from_numlink':
        if ($value) {
          $value = t('enabled');
        }
        else {
          $value = t('disabled');
        }
        $label = t('Allow users to reply to a comment by clicking on comment #NUM link:');
        break;

      case 'comment_easy_reply_replytip_activated':
        if ($value) {
          $value = t('enabled');
        }
        else {
          $value = t('disabled');
        }
        $label = t('Reply tooltip on comment number permalink:');
        break;

      case 'comment_easy_reply_fragment_activated':
        if ($value) {
          $value = t('enabled');
        }
        else {
          $value = t('disabled');
        }
        $label = t('Custom url fragment:');
        break;

      case 'comment_easy_reply_link_mode':
        $label = t('Referrer link type:');
        break;

      case 'comment_easy_reply_replytip_text':
        $label = t('Text inside comment reply tooltip:');
        break;

      case 'comment_easy_reply_referrertip_text':
        $label = t('Text inside comment referrer tooltip:');
        break;

      case 'comment_easy_reply_fragment_text':
        $label = t('Url fragment custom text:');
        break;

      case 'comment_easy_reply_filter':
        $label = t('Tooltip filter:');
        $filter_info = filter_formats();
        foreach ($filter_info as $name => $filter) {
          if ($name == $value) {
            $value = $filter->name;
            break;
          }
        }
        break;

      case 'comment_easy_reply_quote_tooltip':
        if ($value) {
          $value = t('enabled');
        }
        else {
          $value = t('disabled');
        }
        $label = t('Quote reply inside a tooltip:');
        break;

    }
    $item = $label . ' <strong>' . $value . '</strong>';
    $settings[] = array(
      'data' => $item,
    );
  }
  return theme('item_list', array('items' => $settings));
}

/**
 * Adds Comment Easy Reply tooltip markup to a quote output.
 *
 * @param array $vars
 *   An associative array with the following structure:
 *   'quote_content' - The quote's string content.
 *   'quote_author'  - The name of the author of the quote.
 *   'nest'          - The nesting level. It is useful for the recursion system.
 *   'attributes'    - The attributes inserted in quote bbcode by the user.
 *
 * @return string
 *   Themed quote eventually containing Comment Easy Reply toltip markup.
 */
function theme_comment_easy_reply_quote(&$vars) {
  $quote_output = theme('quote', $vars);
  if (isset($vars['attributes']) && isset($vars['attributes']['reply'])) {
    list($nid, $cid) = explode('/', $vars['attributes']['reply']);
    if ($nid) {
      $node = node_load($nid);
      if ($node && _comment_easy_reply_is_node_type_active($node->type)
      && _comment_easy_reply_get_settings_value('comment_easy_reply_quote_tooltip', $node->type)) {
        $comment = comment_load($cid);
        $number = _comment_easy_reply_get_comment_number($comment);
        if (!empty($comment)) {
          /*$page = _comment_easy_reply_get_comment_page($comment);
          $query = drupal_get_query_parameters();
          if (!is_null($page)) {
            if ($page > 0 || ($page == 0 && isset($_GET['page']) && $page == $_GET['page'])) {
              $query['page'] = $page;
            }
            elseif ($page == 0 && isset($_GET['page']) && $page != $_GET['page'] && isset($query['page'])) {
              unset($query['page']);
            }
          }
          $fragment = 'comment-' . $comment->cid;
          $node_type = _comment_easy_reply_get_comment_node_type($comment);
          if (_comment_easy_reply_get_settings_value('comment_easy_reply_fragment_activated', $node_type)) {
            $fragment = _comment_easy_reply_get_settings_value('comment_easy_reply_fragment_text', $node_type);
            $fragment = token_replace($fragment, array('comment' => $comment));
          }*/
          $classes = array('comment-easy-reply-add-quote');
          $referrer_link = theme('comment_easy_reply_comment_referrer_link',
            array(
              'comment' => $comment,
              'comment_easy_reply_comment_num' => $number,
              'more_class' => $classes,
            )
          );
          $classes = array('comment-easy-reply-added-quote');
          $quote_output = _comment_easy_reply_comment_body_replace($quote_output, $nid, FALSE);
          $referrer_tips = theme('comment_easy_reply_comment_referrer_tips',
            array(
              'comment' => $comment,
              'comment_easy_reply_comment_num' => $number,
              'override_text' => $quote_output,
              'more_class' => $classes,
            )
          );
          $quote_output = $referrer_link . $referrer_tips;
          $js = comment_easy_reply_add_js(
            array(
              'comment' => $comment,
              'comment_easy_reply_comment_num' => $number,
            ));
        }
      }
    }
  }
  return $quote_output;
}

/**
 * Returns an HTML list of recent comments to be displayed on comment block.
 *
 * @ingroup themeable
 * @see theme_comment_block()
 */
function theme_comment_easy_reply_comment_block() {
  $items = array();
  $number = variable_get('comment_block_count', 10);
  foreach (comment_get_recent($number) as $comment) {
    $options['tag'] = array();
    $options['tag_link'] = FALSE;
    $matches = _comment_easy_reply_get_matches($comment->subject);
    if (!empty($matches)) {
      foreach ($matches as $num) {
        $parent = NULL;
        $parent_cid = _comment_easy_reply_get_comment_cid_from_num($num, $comment->nid);
        $parent = comment_load($parent_cid);
        if (!empty($parent)) {
          $options['tag'][$num] = _comment_easy_reply_get_tag($parent, TRUE);
        }
      }
    }
    $comment->subject = _comment_easy_reply_comment_body_replace($comment->subject, $comment->nid, FALSE, $options);
    $items[] = l($comment->subject, 'comment/' . $comment->cid, array('fragment' => 'comment-' . $comment->cid)) . '&nbsp;<span>' . t('@time ago', array('@time' => format_interval(REQUEST_TIME - $comment->changed))) . '</span>';
  }
  if ($items) {
    return theme('item_list', array('items' => $items));
  }
  else {
    return t('No comments available.');
  }
}
