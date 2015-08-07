<?php

/**
 * Callback function to get info about style plugin.
 */

/*$plugin = array(
  'title' => t('ADYAX Rounded corners'),
  'description' => t('Presents the panes or panels with a rounded corner box around them'),
  //'render region' => 'panels_rounded_corners_style_render_region',
  'render pane' => 'adyax_test_adyaxteststyle_render_pane',
  'settings form' => 'adyax_test_adyaxteststyle_settings_form',
  'hook theme' => array(
    'adyax_test_adyaxteststyle' => array(
      'variables' => array('content' => NULL),
      'path' => panels_get_path('plugins/styles'),
      'template' => 'adyax-teststyle',
    ),
  ),
);*/

function adyax_test_adyaxteststyle_panels_styles() {
  return array(
    'title' => t('ADYAX Rounded corners'),
    'description' => t('Presents the panes or panels with a rounded corner box around them'),
    //'render region' => 'panels_rounded_corners_style_render_region',
    'render pane' => 'adyax_test_adyaxteststyle_render_pane',
    'pane settings form' => 'adyax_test_adyaxteststyle_style_settings_form',
    'pane settings form submit' => 'adyax_test_adyaxteststyle_style_settings_form_submit',
    'hook theme' => array(
      'adyax_test_adyaxteststyle' => array(
        'variables' => array('content' => NULL),
        'path' => drupal_get_path('module', 'adyax_test') . '/plugins/styles',
        'template' => 'adyax-teststyle',
      ),
    ),
  );
}

/**
 * Render callback for Adyax test style plugin.
 */
function theme_adyax_test_adyaxteststyle_render_pane($vars) {

  $content = $vars['content'];
  $pane = $vars['pane'];
  $display = $vars['display'];

  if (empty($content->content)) {
    return;
  }

  $border_width = 0;
  if (isset($pane->style['settings']['border_width'])) {
    $border_width = $pane->style['settings']['border_width'];
  }

  $output = theme('panels_pane', array('content' => $content, 'pane' => $pane, 'display' => $display));
  $output = theme('adyax_test_adyaxteststyle', array('content' => $output, 'border_width' => $border_width));
  return $output;
}

/**
 * Settings form callback.
 */
function adyax_test_adyaxteststyle_style_settings_form($style_settings) {
  $form['border_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Border width for pane'),
    '#description' => t('Enter the numeric value in px. for border width.'),
    '#required' => TRUE,
    '#default_value' => (isset($style_settings['border_width'])) ? $style_settings['border_width'] : '',
  );
  return $form;
}

function adyax_test_adyaxteststyle_style_settings_form_submit($form, &$form_state) {

}