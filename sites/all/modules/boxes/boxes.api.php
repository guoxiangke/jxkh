<?php

/**
 * Implements hook_box_types_api_info().
 *
 * Tell the boxes module that you are implemented a plugin and
 * which version of the API are you using.
 *
 * THIS IS REQUIRED
 */
function hook_box_types_api_info() {
  return array(
    'api' => 6,
  );
}

/**
 * Implements hook_box_types().
 *
 * Boxes uses ctools plugins to define the block types.
 * All plugin files must be registered in the .info file.
 */
function hook_box_types() {
  $plugins = array();

  $plugins['plugin_key'] = array(
    'label' => t('Title'),
    'description' => t('Description'),
    // This is optional.  Set it to TRUE if you do not want the plugin to be displayed in the UI
    'abstract' => FALSE,
    'handler' => array(
      'class' => 'ClassName',
      'parent' => 'box',
    ),
  );

  return $plugins;
}

/**
 * Implements hook_boxes_access().
 *
 * Access callback for boxes
 *
 * @param $box
 *  Tthe fully loaded Box object
 * @param $op
 *  The access type of view, edit, delete, create
 * @param $account
 *  The user account
 *
 * @return boolean
 *  True if access is allowed, FALSE if not.
 */
function hook_boxes_access($box, $op, $account) {
  return TRUE;
}

/**
 * Implements hook_boxes_submit().
 *
 * React to the box form submit.
 */
function hook_boxes_form_submit($form, $form_state) {

}
