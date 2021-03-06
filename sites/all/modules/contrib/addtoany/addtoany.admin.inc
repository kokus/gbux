<?php

/**
 * @file
 * Administration settings for AddToAny buttons integration
 */

// Load CSS
drupal_add_css((drupal_get_path('module', 'addtoany') . '/addtoany.admin.css'));

/**
 * Administration settings form.
 *
 * @return
 *   The completed form definition.
 */
function addtoany_admin_settings() {
  $form = array();

  global $base_path;
  $button_img = '<img src="' . $base_path . drupal_get_path('module', 'addtoany') . '/images/%s" width="%d" height="%d"%s />';

  $button_options = array(
    'a2a_svg_32' => sprintf($button_img, 'a2a_32_32.png', 32, 32, ' class="addtoany-round-icon"'),
    'share_16_16.png|16|16' => sprintf($button_img, 'share_16_16.png', 16, 16, ''),
    'share_save_171_16.png|171|16' => sprintf($button_img, 'share_save_171_16.png', 171, 16, ''),
    'share_save_256_24.png|256|24' => sprintf($button_img, 'share_save_256_24.png', 256, 24, ''),
    'custom' => 'Custom button',
	'text'	=> 'Text only',
  );
  
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'addtoany') . '/addtoany.admin.js',
  );

  $form['addtoany_button_settings'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Buttons'),
    '#collapsible'  => TRUE,
    '#collapsed'    => FALSE,
  );
  $form['addtoany_button_settings']['addtoany_buttons_size'] = array(
    '#type'          => 'radios',
    '#title'         => t('Icon size'),
    '#default_value' => variable_get('addtoany_buttons_size', '16'),
    '#options'       => array(
      '32' => t('Large (32 x 32 pixels, SVG format, modern)'),
      '16' => t('Small (16 x 16 pixels, PNG format, traditional)'),
    ),
    '#description'   => t('AddToAny\'s large SVG icons are mobile ready, pixel perfect on high DPI or retina displays, and revert to PNG in older browsers.'),
  );
  $form['addtoany_button_settings']['addtoany_service_button_settings'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Service Buttons'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['addtoany_button_settings']['addtoany_service_button_settings']['addtoany_additional_html'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Service Buttons HTML code'),
    '#default_value' => variable_get('addtoany_additional_html', ''),
    '#description'   => t('You can add HTML code to display customized <a href="http://www.addtoany.com/buttons/customize/standalone_services" target="_blank">standalone service buttons</a> next to each universal sharing button. For example: <br /> <code>&lt;a class=&quot;a2a_button_facebook&quot;&gt;&lt;/a&gt;<br />&lt;a class=&quot;a2a_button_twitter&quot;&gt;&lt;/a&gt;<br />&lt;a class=&quot;a2a_button_pinterest&quot;&gt;&lt;/a&gt;</code>
    '),
  );
  $form['addtoany_button_settings']['addtoany_service_button_settings']['addtoany_additional_html_placement'] = array(
    '#type'          => 'radios',
    '#title'         => t('Service Buttons placement'),
    '#default_value' => variable_get('addtoany_additional_html_placement', 'before'),
    '#options'       => array(
      'before' => t('Before the universal sharing button'),
      'after' => t('After the universal sharing button'),
    ),
  );
  $form['addtoany_button_settings']['universal_button'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Universal Button'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
    /* #states workaround in addtoany.admin.js */
  );
  $form['addtoany_button_settings']['universal_button']['addtoany_image'] = array(
    '#type'          => 'radios',
    '#title'         => t('Button'),
    '#default_value' => variable_get('addtoany_image', 'share_save_171_16.png|171|16'),
    '#attributes'    => array('class' => array('addtoany-universal-button-option')),
    '#options'       => $button_options,
  );
  $form['addtoany_button_settings']['universal_button']['addtoany_custom_image'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Custom button URL'),
    '#default_value' => variable_get('addtoany_custom_image', ''),
    '#description'   => t('URL to the button image of your choosing. Example: http://example.com/share.png'),
    '#states'        => array(
      // Show only if custom button is selected
      'visible' => array(
        ':input[name="addtoany_image"]' => array('value' => 'custom'),
      ),
    ),
  );
  $form['addtoany_button_settings']['universal_button']['addtoany_image_attributes'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Button image HTML attributes'),
    '#default_value' => variable_get('addtoany_image_attributes', 'alt="Share"'),
    '#description'   => t('Extra HTML attributes for img tag. Example: alt=""'),
  );
  $form['addtoany_button_settings']['universal_button']['addtoany_link_text'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Link text'),
    '#default_value' => variable_get('addtoany_link_text', ''),
    '#description'   => t('Text for the universal sharing button link. Example: Share'),
  );
  
  $form['addtoany_placement_settings'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Placement'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['addtoany_placement_settings']['addtoany_nodetypes'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Node types'),
    '#description'   => t('Display buttons for these node types.'),
    '#default_value' => variable_get('addtoany_nodetypes', array('page', 'article')),
    '#options'       => node_type_get_names(),
  );
  $form['addtoany_placement_settings']['addtoany_display_in_teasers'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display for node <strong>teasers</strong>'),
    '#default_value' => variable_get('addtoany_display_in_teasers', '1'),
    '#description'   => t('Display buttons for node <strong>teasers</strong> in selected sections.'),
    '#states'        => array(
      // Disable if no section placement is selected
      'disabled' => array(
        ':input[name="addtoany_display_in_nodecont"]' => array('checked' => FALSE),
        ':input[name="addtoany_display_in_nodelink"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['addtoany_placement_settings']['addtoany_display_in_nodelink'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display in <strong>link</strong> section'),
    '#default_value' => variable_get('addtoany_display_in_nodelink', '1'),
    '#description'   => t('Display buttons in the <strong>link</strong> section of node pages.'),
  );
  $form['addtoany_placement_settings']['addtoany_display_in_nodecont'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display in <strong>content</strong> section'),
    '#default_value' => variable_get('addtoany_display_in_nodecont', '0'),
    '#description'   => t('Display buttons in the <strong>content</strong> section of node pages.'),
  );
  $form['addtoany_placement_settings']['addtoany_display_weight'] = array(
    '#type'          => 'weight',
    '#title'         => t('Content weight'),
    '#default_value' => variable_get('addtoany_display_weight', 40),
    '#delta'         => 50,
    '#description'   => t('Optional weight value for buttons displayed in the <strong>content</strong> section.'),
    '#states'        => array(
      // Show only if placement in "content" selected
      'visible' => array(
        ':input[name="addtoany_display_in_nodecont"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['addtoany_additional_settings'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Additional options'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['addtoany_additional_settings']['addtoany_additional_js'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Additional JavaScript'),
    '#default_value' => variable_get('addtoany_additional_js', ''),
    '#description'   => t('You can add special JavaScript code for AddToAny. Advanced users might want to check out AddToAny\'s <a href="http://www.addtoany.com/buttons/api/" target="_blank">JavaScript API</a> and <a href="http://www.addtoany.com/buttons/customize/" target="_blank">documentation</a>.'),
  );
  $form['addtoany_additional_settings']['addtoany_no_3p'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Disable 3rd party cookies'),
    '#default_value' => variable_get('addtoany_no_3p', '0'),
    '#description'   => t('Disabling may affect analytics and limit some functionality.'),
   );

  return system_settings_form($form);
}
