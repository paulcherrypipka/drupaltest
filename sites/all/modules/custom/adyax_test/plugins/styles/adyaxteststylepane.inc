<?php

/**
 * Callback function to get info about style plugin.
 */

function adyax_test_adyaxteststylepane_panels_styles() {
  return array(
    'title' => t('ADYAX pane with border'),
    'description' => t('Presents the panes or panels with a rounded corner box around them'),
    'render pane' => 'adyax_test_adyaxteststylepane_render_pane',
    'pane settings form' => 'adyax_test_adyaxteststylepane_style_settings_form',
    'pane settings form submit' => 'adyax_test_adyaxteststylepane_style_settings_form_submit',
    'hook theme' => array(
      'adyax_test_adyaxteststylepane' => array(
        'variables' => array('content' => NULL),
        'path' => drupal_get_path('module', 'adyax_test') . '/plugins/styles',
        'template' => 'adyax-teststyle-pane',
      ),
    ),
  );
}

/**
 * Render callback for pane Adyax test style plugin.
 */
function theme_adyax_test_adyaxteststylepane_render_pane($vars) {

  $content = $vars['content'];
  $pane = $vars['pane'];
  $display = $vars['display'];

  if (empty($content->content)) {
    return;
  }

  $border_width_pane = 0;
  if (isset($pane->style['settings']['border_width_pane']) && is_numeric($pane->style['settings']['border_width_pane'])) {
    $border_width_pane = $pane->style['settings']['border_width_pane'];
  }

  $output = theme('panels_pane', array('content' => $content, 'pane' => $pane, 'display' => $display));
  $output = theme('adyax_test_adyaxteststylepane', array('content' => $output, 'border_width_pane' => $border_width_pane));
  return $output;
}

/**
 * Settings form callback.
 */
function adyax_test_adyaxteststylepane_style_settings_form($style_settings) {
  $form['border_width_pane'] = array(
    '#type' => 'textfield',
    '#title' => t('Border width for pane'),
    '#description' => t('Enter the numeric value in px. for border width.'),
    '#required' => TRUE,
    '#default_value' => (isset($style_settings['border_width_pane'])) ? $style_settings['border_width_pane'] : '',
  );
  $form['#validate'][] = 'adyax_test_adyaxteststylepane_style_settings_form_validate';
  return $form;
}

function adyax_test_adyaxteststylepane_style_settings_form_validate(&$form, &$form_state) {
  if (!is_numeric($form_state['values']['border_width_pane'])) {
    form_set_error('edit-settings-border-width-pane', t('Border width value must be a numeric value'));
  }
}