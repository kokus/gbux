<?php
/**
 * Custom Galeria Template settings
 */
 
/**
 * page alter
 */
function creatrix_page_alter(&$vars) {

	// Add custom varibales for scss
	$theme = superhero_get_theme();
	$theme->custom['header_height'] = theme_get_setting('superhero_header_height');
	$theme->custom['header_fixed_height'] = theme_get_setting('superhero_header_fixed_height');
	$theme->custom['custom_color_main_lighter'] = $theme->settings['custom_color_main_lighter'];
	$theme->custom['custom_color_header_background'] = $theme->settings['custom_color_header_background'];
	$theme->custom['custom_color_header_link'] = $theme->settings['custom_color_header_link'];
	$theme->custom['custom_color_background'] = $theme->settings['custom_color_background'];
	$theme->custom['custom_color_button_link'] = $theme->settings['custom_color_button_link'];
	$theme->custom['custom_color_bottom_background'] = $theme->settings['custom_color_bottom_background'];
	$theme->custom['custom_color_footer_background'] = $theme->settings['custom_color_footer_background'];
	// Remove content from front page
	if (drupal_is_front_page()) {
		unset($vars['data']['content']);
	}
}

function creatrix_preprocess_page(&$variables) {
  if (!empty($variables['node']) && $variables['node']->type == 'article') {
    $variables['title'] = FALSE;
  }
}

/**
 * Preprocess node
 */
function creatrix_preprocess_node(&$vars) {
   
  if ($vars['view_mode'] == 'teaser_alt') {
    $vars['theme_hook_suggestions'][] = 'node__' . $node->type . '__teaser__alt';
    $vars['theme_hook_suggestions'][] = 'node__' . $node->nid . '__teaser_alt';
  }
}

/**
 * Preprocess node
 * Added by JV 05/21
 * For blocks with background and text with a aligned list. Add a class 
 * for this block of 'text-list-background'. if this class exist for block
 * this function will remove the superhero template and use the default block one
 */
function creatrix_preprocess_block(&$vars) {

	if (in_array('list-text-background', $vars['classes_array'])) {
		if($vars['theme_hook_suggestions'][3] == 'block__superhero') {
			unset($vars['theme_hook_suggestions'][3]);
		}
		//dpm($vars);
	}
	
}

function creatrix_preprocess_taxonomy_term($vars){
	
}

function creatrix_preprocess_region(&$variables) {
   
   //get node id of rendered node
  	$node = menu_get_object();
  	if (isset($node->nid)) {
  		$nid = $node->nid;
   	}

   	//  Modify order stack up on mobile for blocks Homepage
    if ($variables["is_front"]) {
    	$region = $variables['region'];	
    	if(in_array($region, array('feature_first'))) {
	  		$variables['classes_array'][] = 'col-sm-pull-7';
	 	}
	 	if(in_array($region, array('feature_second'))) {
	  		$variables['classes_array'][] = 'col-sm-push-5';
	 	}

    }  

   	
   	/* Removed 03-20 JV
  	if (isset($nid) && ($nid == 3)) :
		$region = $variables['region'];
		if(in_array($region, array('user_first'))) {
	  		$variables['classes_array'][] = 'col-sm-push-7';
	 	}
	 	if(in_array($region, array('user_second'))) {
	  		$variables['classes_array'][] = 'col-sm-pull-5';
	 	}
	 	if(in_array($region, array('feature_first'))) {
	  		$variables['classes_array'][] = 'col-sm-push-7';
	 	}
	 	if(in_array($region, array('feature_second'))) {
	  		$variables['classes_array'][] = 'col-sm-pull-5';
	 	}
	endif;
	*/
}

/**
 * Implement hook_breadcrumd
 * Added to include note->title to default drupal breadcrumb
 */
function creatrix_breadcrumb($variables) {
	$breadcrumb = $variables['breadcrumb'];
  	if (!empty($breadcrumb)) {
	    // Adding the title of the current page to the breadcrumb.
	    $breadcrumb[] = drupal_get_title();


	    // Provide a navigational heading to give context for breadcrumb links to
	    // screen-reader users. Make the heading invisible with .element-invisible.
	    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';


	    $output .= '<div class="breadcrumb">' . implode(' › ', $breadcrumb) . '</div>';
	    return $output;
  	}
}
