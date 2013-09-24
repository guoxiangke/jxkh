<?php

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
 * Bootstrap theme wrapper function for the primary menu links
 */
function bootstrap_sbq_menu_tree__primary(&$variables) {
  return '<ul class="menu nav nav-pills nav-justified">' . $variables['tree'] . '</ul>';
}

/**
 * Bootstrap theme wrapper function for the secondary menu links
 */
function bootstrap_sbq_menu_tree__secondary(&$variables) {
  return '<ul class="menu nav nav-pills pull-right">' . $variables['tree'] . '</ul>';
}

/**
 * Preprocessor for theme('button').
 */
function bootstrap_sbq_preprocess_button(&$vars) {
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
function bootstrap_sbq_textfield($variables) {
  $element = $variables['element'];
  $output = '';
  // login form adding glyphicon.
  if($element['#name'] == 'name') {
    $output = '<span class="input-group-addon"><span class="glyphicon glyphicon-user"></span></span>';
  }
 
  // force type.
  $element['#attributes']['type'] = 'text';
  // set placeholder.
  if(isset($variables['element']['#description'])){
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
function bootstrap_sbq_password($variables) {
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

