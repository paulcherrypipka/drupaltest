<?php

/**
 * Callback function to get info a list of content types.
 */
function adyax_test_adyaxtest_ctools_content_types() {
  return array(
    'single' => TRUE,
    'title' => t('adyaxtest'),
    'content_types' => 'adyaxtest',
    'description' => t('Adyax test CCT'),
    'render callback' => 'adyax_test_adyaxtest_content_type_render',
    //'edit form' => 'adyax_test_adyaxtest_content_type_edit_form',
    'category' => t('Adyaxtest'),
    'all contexts' => TRUE,
    'hook theme' => 'adyax_test_adyaxtest_theme',
    'defaults' => array(),
  );
}

/**
 * Render callback for Adyax test CT
 */
function adyax_test_adyaxtest_content_type_render($subtype, $conf, $panel_args, $contexts) {
  $block = new stdClass();
  $rendered_nodes = _adyax_test_get_rendered_random_nodes(3);
  $block->title = 'Adyax test three random';
  $block->content = array(
    '#theme' => 'adyax_test_adyaxtheme',
    '#nodes' => $rendered_nodes,
    //'#border_width' => $conf['border_width'],
  );
  return $block;
}

/**
 * Implements hook_theme().
 */
function adyax_test_adyaxtest_theme(&$theme, $plugin) {
  $theme['adyax_test_adyaxtheme'] = array(
    'path' => $plugin['path'],
    'template' => 'adyax-test',
    'variables' => array(
      'nodes' => array(),
      //'border_width' => NULL,
    ),
  );
}

/**
 * Get three rendered random nodes.
 */
function _adyax_test_get_rendered_random_nodes($max) {
  $query = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('n.status', 1, '=')
    ->orderRandom('n.nid')
    ->range(0, $max)
    ->execute();

  $results = $query->fetchCol();

  $rendered_nodes = array();
  foreach($results as $result) {
    $node = node_load($result);
    $node_params = node_view($node, 'teaser');
    $rendered_nodes[] = drupal_render($node_params);
  }
  return $rendered_nodes;
}

/**
 * Callback for build settings form.
 */
//function adyax_test_adyaxtest_content_type_edit_form($form, &$form_state) {
//  $conf = $form_state['conf'];
//  $form['border_width'] = array(
//    '#type'    => 'textfield',
//    '#title'   => t('Border width'),
//    '#required' => TRUE,
//    '#default_value' => (isset($conf['border_width'])) ? $conf['border_width'] : 1,
//  );
//  return $form;
//}

//function adyax_test_adyaxtest_content_type_edit_form_submit(&$form, &$form_state) {
//  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
//    $form_state['conf'][$key] = $form_state['values'][$key];
//  }
//}

//function adyax_test_adyaxtest_content_type_edit_form_validate(&$form, &$form_state) {
//  if (!is_numeric($form_state['values']['border_width'])) {
//    form_set_error('edit-border-width', t('Border width value must be a numeric value'));
//  }
//}
