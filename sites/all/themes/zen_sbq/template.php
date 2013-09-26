<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728096
 */


/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_maintenance_page(&$variables, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  STARTERKIT_preprocess_html($variables, $hook);
  STARTERKIT_preprocess_page($variables, $hook);
}
// */

/**
 * Override or insert variables into the html templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("html" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_html(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');

  // The body tag's classes are controlled by the $classes_array variable. To
  // remove a class from $classes_array, use array_diff().
  //$variables['classes_array'] = array_diff($variables['classes_array'], array('class-to-remove'));
}
// */

/**
 * Override or insert variables into the page templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_page(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_node(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');

  // Optionally, run node-type-specific preprocess functions, like
  // STARTERKIT_preprocess_node_page() or STARTERKIT_preprocess_node_story().
  $function = __FUNCTION__ . '_' . $variables['node']->type;
  if (function_exists($function)) {
    $function($variables, $hook);
  }
}
// */

/**
 * Override or insert variables into the comment templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_comment(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the region templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("region" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_region(&$variables, $hook) {
  // Don't use Zen's region--sidebar.tpl.php template for sidebars.
  //if (strpos($variables['region'], 'sidebar_') === 0) {
  //  $variables['theme_hook_suggestions'] = array_diff($variables['theme_hook_suggestions'], array('region__sidebar'));
  //}
}
// */

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_block(&$variables, $hook) {
  // Add a count to all the blocks in the region.
  // $variables['classes_array'][] = 'count-' . $variables['block_id'];

  // By default, Zen will use the block--no-wrapper.tpl.php for the main
  // content. This optional bit of code undoes that:
  //if ($variables['block_html_id'] == 'block-system-main') {
  //  $variables['theme_hook_suggestions'] = array_diff($variables['theme_hook_suggestions'], array('block__no_wrapper'));
  //}
}
// */
/**
 * @file template.php
 */
function _bootstrap_content_col_md($columns = 1) {
  $class = FALSE;
  
  switch($columns) {
    case 1:
      $class = '12';
      break;
    case 2:
      $class = '8';
      break;
    case 3:
      $class = '5';
      break;
  }
  
  return $class;
}

/**
 * Preprocess variables for page.tpl.php
 *
 * @see page.tpl.php
 */
function zen_sbq_preprocess_page(&$variables) {
  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 3;
  }
  elseif (!empty($variables['page']['sidebar_first'])) {
    $variables['columns'] = 2;
  }
  elseif (!empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 2;
  }
  else {
    $variables['columns'] = 1;
  }

  // Primary nav
  $variables['primary_nav'] = FALSE;
  if ($variables['main_menu']) {
    // Build links
    $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    // Provide default theme wrapper function
    $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
  }

  // Secondary nav
  $variables['secondary_nav'] = FALSE;
  if ($variables['secondary_menu']) {
    // Build links
    $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    // Provide default theme wrapper function
    $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
  }  
  //page level id for specific theme
  //use case:if you have a page like this: http://example.com/mypage,
  //and you want add a css ID on that page:<div id="mypage">..</div>,
  //you can push the "mypage" to $specific_pages.
  $variables['page_id'] = 'page';
  $variables['page_class'] = 'page';
  if(arg(0) == 'questions') {
    $variables['page_id'] = 'questions';
    if(is_numeric(arg(1))) {
      // $variables['page_id'] = 'page-question-'.arg(1);
      $variables['page_class'] = 'page-question';
    }elseif(arg(1) == 'tagged'){      
      // $variables['page_id'] = 'page-questions-tagged';
      $variables['page_class'] = 'page-questions-list';
    }else{      
      // $variables['page_id'] = 'page-questions';
      $variables['page_class'] = 'page-questions-list';
    }
  }
  if(drupal_is_front_page()) {
    $variables['page_id'] = 'page-front';
  }
  if( arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
    if($node->nid) $variables['page_id'] = 'page-node-'.$node->nid;
    if($node->nid) $variables['page_class'] = 'page-'.$node->type;
  }
}
/**
 * Bootstrap theme wrapper function for the primary menu links
 */
function zen_sbq_menu_tree__primary(&$variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}

/**
 * Bootstrap theme wrapper function for the secondary menu links
 */
function zen_sbq_menu_tree__secondary(&$variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}

/**
 * Preprocessor for theme('button').
 */
function zen_sbq_preprocess_button(&$vars) {
  $vars['element']['#attributes']['class'][] = 'btn btn-default';

  if (isset($vars['element']['#value'])) {
    $classes = array(
      //specifics
      t('Save and add') => 'btn-info',
      t('Add another item') => 'btn-info',
      t('Add effect') => 'btn-primary',
      t('Add and configure') => 'btn-primary',
      t('Update style') => 'btn-primary',
      t('Download feature') => 'btn-primary',

      //generals
      t('Save') => 'btn-primary',
      t('Apply') => 'btn-primary',
      t('Create') => 'btn-primary',
      t('Confirm') => 'btn-primary',
      t('Submit') => 'btn-primary',
      t('Export') => 'btn-primary',
      t('Import') => 'btn-primary',
      t('Restore') => 'btn-primary',
      t('Rebuild') => 'btn-primary',
      t('Search') => 'btn-primary',
      t('Add') => 'btn-info',
      t('Update') => 'btn-info',
      t('Delete') => 'btn-danger',
      t('Remove') => 'btn-danger',
    );
    foreach ($classes as $search => $class) {
      if (strpos($vars['element']['#value'], $search) !== FALSE) {
        $vars['element']['#attributes']['class'][] = $class;
        break;
      }
    }
  }
}

/**
 * @see http://www.hbensalem.com/php/drupal-7-and-bootstrap-3-theming-the-login-form/
 */
/**** theme form textfields. ***/
function zen_sbq_textfield($variables) {
  $element = $variables['element'];
  $output = '';
  // login form adding glyphicon.
  if($element['#name'] == 'name') {
    $output = '<span class="input-group-addon"><span class="glyphicon glyphicon-user"></span></span>';
  }
 
  // force type.
  $element['#attributes']['type'] = 'text';
  // set placeholder.
  if(isset($variables['element']['#description']) && !isset($element['#attributes']['placeholder'])){
    $element['#attributes']['placeholder'] = $variables['element']['#description'];
  }
 
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  // adding bootstrap classes.
  _form_set_class($element, array('form-text', 'form-control', 'input-lg-3'));
 
  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';
 
    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }
 
  $output .= '<input' . drupal_attributes($element['#attributes']) . ' />';
 
  return $output . $extra;
}

/*** theme password field ***/
function zen_sbq_password($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'password';
  element_set_attributes($element, array('id', 'name', 'size', 'maxlength'));
  _form_set_class($element, array('form-text', 'form-control'));
 
  $output = '';
  // login form adding glyphicon.
  if($element['#name'] == 'pass') {
    $output = '<span class="input-group-addon"><span class="glyphicon glyphicon-eye-close"></span></span>';
  }
 
  return $output . '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/** Theme form element **/
function zen_sbq_form_element($variables) {
  $element = &$variables['element'];
 
  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );
 
  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  if (isset($element['#parents']) && form_get_error($element)) {
    $attributes['class'][] = 'has-error';
  }
 
  if($element['#type'] != 'radio' && $element['#type'] != 'textarea'){
    $attributes['class'][] = 'input-group';
  }
 
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";
 
  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';
 
  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
 
    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;
 
    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }
  // remove description we'll use placeholder.
  if (!empty($element['#description'])) {
    //$output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }
 
  $output .= "</div>\n";
 
  return $output;
}

/**
 * Preprocess variables for region.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("region" in this case.)
 */
function zen_sbq_preprocess_region(&$variables, $hook) {
  // Sidebar regions get some extra classes and a common template suggestion.
  if (strpos($variables['region'], 'sidebar_') === 0) {
    $variables['classes_array'][] = 'column';
    $variables['classes_array'][] = 'sidebar';
    // Allow a region-specific template to override Zen's region--sidebar.
    array_unshift($variables['theme_hook_suggestions'], 'region__'.$variables['region']);
  }
  // Use a template with no wrapper for the content region.
  elseif ($variables['region'] == 'content') {
    // Allow a region-specific template to override Zen's region--no-wrapper.
    array_unshift($variables['theme_hook_suggestions'], 'region__no_wrapper');
  }
  // Add a SMACSS-style class for header region.
  elseif ($variables['region'] == 'header') {
    array_unshift($variables['classes_array'], 'header__region');
  }
}

/**
 * Implements hook_form_alter().
 */
function zen_sbq_form_alter(&$form, &$form_state, $form_id) {
  
  if($form_id == 'user_login_block') {
    $form['remember_me']['#default_value'] = FALSE;
    $form['actions']['#weight'] = 6;
    $form['links']['#weight'] = 7;
    $form['submitted']['#weight'] = 8;
    $form['name']['#attributes']['placeholder'] = '邮箱/手机号/用户名';
    $form['pass']['#attributes']['placeholder'] = '请输入密码';
  }
}