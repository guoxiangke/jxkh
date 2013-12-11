<?php
/**
 * @file
 * sbq_event_features.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbq_event_features_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'add event node registration'.
  $permissions['add event node registration'] = array(
    'name' => 'add event node registration',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node_registration',
  );

  // Exported permission: 'administer node registration'.
  $permissions['administer node registration'] = array(
    'name' => 'administer node registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node_registration',
  );

  // Exported permission: 'cancel own event node registration'.
  $permissions['cancel own event node registration'] = array(
    'name' => 'cancel own event node registration',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node_registration',
  );

  // Exported permission: 'delete own event node registration'.
  $permissions['delete own event node registration'] = array(
    'name' => 'delete own event node registration',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node_registration',
  );

  // Exported permission: 'edit own event node registration'.
  $permissions['edit own event node registration'] = array(
    'name' => 'edit own event node registration',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node_registration',
  );

  // Exported permission: 'other node registration'.
  $permissions['other node registration'] = array(
    'name' => 'other node registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node_registration',
  );

  // Exported permission: 'view event node registration'.
  $permissions['view event node registration'] = array(
    'name' => 'view event node registration',
    'roles' => array(),
    'module' => 'node_registration',
  );

  // Exported permission: 'view own event node registration'.
  $permissions['view own event node registration'] = array(
    'name' => 'view own event node registration',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node_registration',
  );

  return $permissions;
}
