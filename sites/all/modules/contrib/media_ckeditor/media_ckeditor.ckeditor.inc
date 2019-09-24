<?php

/**
 * @file
 * Provides Media: WYSIWYG integration for CKEditor.
 */

/**
 * Implements hook_ckeditor_plugin_alter().
 *
 * @todo: convert this to hook_ckeditor_plugin() when
 * https://www.drupal.org/node/2542566 is fixed.
 */
function media_ckeditor_ckeditor_plugin_alter(&$plugins) {
  // Override the default CKEditor Media plugin.
  $plugins['media'] = array(
    'name' => 'media',
    'desc' => t('Plugin for inserting images from Drupal media module'),
    'path' => base_path() . drupal_get_path('module', 'media_ckeditor') . '/js/plugins/media/',
    'buttons' => array(
      'Media' => array(
        'icon' => 'images/icon.gif',
        'label' => 'Add media',
      ),
    ),
    'default' => 'f',
  );
}

/**
 * Implements hook_ckeditor_settings_alter().
 */
function media_ckeditor_ckeditor_settings_alter(&$settings, $conf) {
  if (array_key_exists('media', $settings['loadPlugins'])) {
    module_load_include('inc', 'media', 'includes/media.browser');

    $javascript = media_browser_js();

    foreach ($javascript as $key => $definitions) {
      foreach ($definitions as $definition) {
        $function = 'drupal_add_' . $key;
        call_user_func_array($function, $definition);
      }
    }

    drupal_add_js(drupal_get_path('module', 'media_ckeditor') . '/js/plugins/media/library.js', array('scope' => 'footer', 'weight' => -20));
  }
}
