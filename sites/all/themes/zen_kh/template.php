<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728096
 */

function zen_kh_preprocess_page(&$vars, $hook) {
  if (isset($vars['node'])) {
    // If the node type is "blog_madness" the template suggestion will be "page--blog-madness.tpl.php".
    // $vars['theme_hook_suggestions'][] = 'page__'. $vars['node']->type;
    array_unshift($vars['theme_hook_suggestions'],'page__node__'. $vars['node']->type);
  }
}
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
 * Implements hook_form_alter().
 */
function zen_kh_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'user_login_block') {
    // @see user_login_block
    $items = array();
    if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
//        $items[] = l(t('Create new doctor account'), 'doctor/register', array('attributes' => array('title' => t('Create a new user account.'))));
     
//      $items[] = '<a href="#" title="" data-toggle="modal" class="user_doctor_register_ajax" data-target="#sbq_doctor_quick_login_modal">医生快速通道</a>';                                                                   
      $items[] = '<a href="/doctor/register"  data-toggle="modal" class="user_doctor_register_ajax">' . t('Create new doctor account') . '</a>';
    }
    $form['doctor_register'] = array('#markup' => theme('item_list', array('items' => $items, 'attributes' => array('class' => 'sbq_doctor_register_button'))), '#weight' => -10);

    $items = array();
    if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
      $items[] = l(t('Create new account'), 'customer/register', array('attributes' => array('title' => t('Create a new user account.'))));
    }
    $form['links'] = array('#markup' => theme('item_list', array('items' => $items, 'attributes' => array('class' => 'sbq_customer_register_button'))));

    $items = array();
    $items[] = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));

    # code...
    // $form['actions']['#prefix'] = '<div class="input-prepend input-append">';
    // $form['actions']['#suffix'] = '</div>';
    $form['remember_me_a'] = array('#markup' => theme('item_list', array('items' => $items, 'attributes' => array('class' => 'sbq_request_pass_button'))));

    $items = array();
    if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
      $items[] = l(t('Visit anonymous'), 'qa', array('attributes' => array('title' => t('Create a new user account.'))));
    }
    $form['anonymous_link'] = array('#markup' => theme('item_list', array('items' => $items, 'attributes' => array('class' => 'sbq_anonymous_visit_button'))), '#weight' => 10000);

    $form['actions']['#weight'] = 6;
    $form['links']['#weight'] = 7;
    $form['captcha']['#weight'] = 6;
    $form['submitted']['#weight'] = 9;
    $form['name']['#attributes']['placeholder'] = '邮箱/用户名';
    $form['pass']['#attributes']['placeholder'] = '请输入密码';
  }
  //hide csna links in role register(doctor/register customer/register)
  if ($form_id == 'user_login' || $form_id == 'user_login_block' || $form_id == 'user_register_form') {
    if (arg(1) == 'register')
      $form['submitted']['user_login_block']['#access'] = FALSE;
  }

}


function zen_kh_preprocess_html(&$variables) {
  global $user;
  if(!$user->uid) {
    //http://adaptivethemes.com/how-to-add-css-files-in-drupal-7
    //http://friendlymachine.net/posts/2011/add-stylesheet-drupal-theme
    drupal_add_css(drupal_get_path('theme', 'zen_kh') . '/css/register.css', array('group' => CSS_THEME));

    module_load_include('inc', 'profile2_regpath', 'registration_form');

    $customer_register_form = drupal_get_form('user_register_form');
    unset($customer_register_form['profile_doctor_profile']);
    unset($customer_register_form['profile_doctor_private_profile']);
    $variables['customer_register_form'] = drupal_render($customer_register_form);

    $doctor_register_form = drupal_get_form('user_register_form');
    unset($doctor_register_form['profile_customer_profile']);
    unset($doctor_register_form['profile_patient_private_profile']);
    $variables['doctor_register_form'] = drupal_render($doctor_register_form);
    
//    $user_login_form = drupal_get_form('user_login');
//    $variables['user_login_form'] = drupal_render($user_login_form);
//    $quick_register = drupal_get_form('user_register_form');
//    $variables['doctor_quick_login_form'] = drupal_render($quick_register);
//    $quick_login = drupal_get_form('user_login');
//    $variables['user_login_block'] =  drupal_render($quick_login);
  }
}

/*
 * Remove user profile default content
 */
function zen_kh_preprocess_user_profile (&$variables, $hook) {
  unset($variables['user_profile']);
}

/**
 * Implements hook_block_view_alter().
 */
function zen_kh_block_view_alter(&$data, $block) {
  $relationship_page_expect = array(
    'related_questions2-block',
    'news-block_2',
    'news-block_1',
    'recommond_doctors',
    'recommond_patients',
    'exposure_platform-block_user',
    'blog-block',
  );
  if(in_array($block->delta, $relationship_page_expect) && arg(2) == 'relationship') {
    unset($data['content']); 
  }
}