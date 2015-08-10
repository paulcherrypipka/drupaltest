<?php

/**
 * Callback function to get info about style plugin.
 */

function adyax_test_adyaxteststyleregion_panels_styles() {
  return array(
    'title' => t('ADYAX region with border'),
    'description' => t('Presents the panes or panels with a rounded corner box around them'),
    'render region' => 'adyax_test_adyaxteststyleregion_render_region',
    'settings form' => 'adyax_test_adyaxteststyleregion_style_settings_form',
    'settings form submit' => 'adyax_test_adyaxteststyleregion_style_settings_form_submit',
    'hook theme' => array(
      'adyax_test_adyaxteststyleregion' => array(
        'variables' => array('content' => NULL),
        'path' => drupal_get_path('module', 'adyax_test') . '/plugins/styles',
        'template' => 'adyax-teststyle-region',
      ),
    ),
  );
}

/**
 * Render callback for Adyax test style plugin.
 */
function theme_adyax_test_adyaxteststyleregion_render_region($vars) {
  $border_width_region = 0;
  if (isset($vars['settings']['border_width_region'])) {
    $border_width_region = $vars['settings']['border_width_region'];
  }

  $output = implode($vars['panes']);
  $output = theme('adyax_test_adyaxteststyleregion', array('content' => $output, 'border_width_region' => $border_width_region));
  return $output;
}

/**
 * Settings form callback.
 */
function adyax_test_adyaxteststyleregion_style_settings_form($style_settings) {
  $form['border_width_region'] = array(
    '#type' => 'textfield',
    '#title' => t('Border width for region'),
    '#description' => t('Enter the numeric value in px. for border width.'),
    '#required' => TRUE,
    '#default_value' => (isset($style_settings['border_width_region'])) ? $style_settings['border_width_region'] : '',
  );
  return $form;
}

function adyax_test_adyaxteststyleregion_style_settings_form_submit($form, &$form_state) {

}