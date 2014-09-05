<?php

/**
 * Callback function to supply a list of content types.
 */
function adyax_test_adyaxtest_ctools_content_types() {
  return array(
    'single' => TRUE,
    'title' => t('adyaxtest'),
    'content_types' => 'adyaxtest',
    'description' => t('adyaxtest CTools CT'),
    'render callback' => 'adyax_test_adyaxtest_content_type_render',
    'edit form' => 'adyax_test_adyaxtest_content_type_edit_form',
    'category' => t('Adyaxtest'),
    'all contexts' => TRUE,
    'hook theme' => 'adyax_test_adyaxtest_theme',
    'defaults' => array('border_width' => 1),
  );
}

/**
 * Output function for the content type
 */
function adyax_test_adyaxtest_content_type_render($subtype, $conf, $panel_args,  $contexts) {

  // Getting 3 random published nodes
  $query = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('n.status', 1, '=')
    ->orderRandom('n.nid')
    ->range(0, 3)
    ->execute();

  $results = $query->fetchCol();

  $rendered_nodes = array();
  foreach($results as $result) {
    $node = node_load($result);
    // Load node parameters for render in teaser view mode
    $node_params = node_view($node, 'teaser');
    $rendered_nodes[] = drupal_render($node_params);
  }

  // Create block with for display nodes
  $block = new stdClass();
  $block->content = array(
    '#theme' => 'adyax_test_adyaxtheme_full',
    '#nodes' => $rendered_nodes,
    '#border_width' => $conf['border_width'],
  );

  return $block;
}

/**
 * Implementation of hook_theme().
 */
function adyax_test_adyaxtest_theme(&$theme, $plugin) {
  $theme['adyax_test_adyaxtheme_full'] = array(
    'path' => $plugin['path'],
    'template' => 'adyaxtest-full',
    'variables' => array(
      'nodes' => array(),
      'border_width' => NULL,
    ),
  );
}

/**
 *Building settings form
 */
function adyax_test_adyaxtest_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // Create field for custom border width style
  $form['border_width'] = array(
    '#type'    => 'textfield',
    '#title'   => t('Border width'),
    '#required' => TRUE,
    '#default_value' => $conf['border_width'],
  );

  return $form;
}

/**
 *Settings form submit handler
 */
function adyax_test_adyaxtest_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

function adyax_test_adyaxtest_content_type_edit_form_validate(&$form, &$form_state) {
  if (!is_numeric($form_state['values']['border_width'])) {
    form_set_error('edit-border-width', t('Border width value must be a numeric value'));
  }
}