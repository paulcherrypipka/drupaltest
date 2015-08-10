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
