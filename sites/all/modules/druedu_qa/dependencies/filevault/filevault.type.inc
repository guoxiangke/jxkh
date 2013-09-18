<?php

/**
 * Implements hook_entity_info().
 *
 * This is the fundamental description of the entity.
 *
 * It provides a single entity with a single bundle and without revision
 * support.
 */
function filevault_entity_info() {
  $info['filevault'] = array(
    // A human readable label to identify our entity.
    'label' => t('File Vault File'),

    // The controller for the File Vault Entity, extending the Drupal core controller.
    'entity class' => 'Entity',
    'controller class' => 'EntityAPIController',

    // The views controller
    'views controller class' => 'EntityDefaultViewsController',

    // Base table defined in hook_schema()
    'base table' => 'filevault_files',

    // Returns the uri elements of an entity
    'uri callback' => 'filevault_uri',

    // Access call back
    'access callback' => 'filevault_access',

    // We will not allow fields to be attached thru the field API, as
    // this would create more joins on each lookup
    'fieldable' => FALSE,

    // entity_keys tells the controller what database fields are used for key
    // functions. It is not required if we don't have bundles or revisions.
    // Here we do not support a revision, so that entity key is omitted.
    'entity keys' => array(
      'id' => 'id' , // The 'id' (basic_id here) is the unique id.
    ),

    // FALSE disables caching. Caching functionality is handled by Drupal core.
    'static cache' => TRUE,

    // Bundles are alternative groups of fields or configuration
    // associated with a base entity type.
    'bundles' => array(),

    // View modes allow entities to be displayed differently based on context.
    // As a demonstration we'll support "Tweaky", but we could have and support
    // multiple display modes.
    'view modes' => array(
        'original' => array(
          'label' => t('Original'),
          'custom settings' => FALSE,
        ),
        'lightbox' => array(
          'label' => t('Lightbox'),
          'custom settings' => FALSE,
        ),
        'embedded' => array(
          'label' => t('Embedded'),
          'custom settings' => FALSE,
        ),
        'icon' => array(
          'label' => t('Icon'),
          'custom settings' => FALSE,
        ),
        'admin' => array(
          'label' => t('Full administartion view of an entity'),
          'custom settings' => FALSE,
        ),
    )
  );

  return $info;
}


/**
 *  Access callback
 *
 */
function filevault_access() {

  // load the current user
  global $user;


/*
  // Look up the access in {filevault_user_access}
  $access = db_query('SELECT {filevault_access}.id
                      FROM   {filevault_access}
                      WHERE  {filevault_access}.read_access = 1
                      AND    {filevault_access}.filevault_path_id = :path_id', array(':path_id' =>$path_id))
                      ->fetchAll();

  // Sorry, you don't have access
  if( count($access) == 0 ){
    return FALSE;
  }

 */

  return TRUE;

}

/**
 * Fetch a basic object.
 *
 * This function ends up being a shim between the menu system and
 * filevault_load_multiple().
 *
 * This function gets its name from the menu system's wildcard
 * naming conventions. For example, /path/%wildcard would end
 * up calling wildcard_load(%wildcard value). In our case defining
 * the path: examples/filevault/basic/%filevault in
 * hook_menu() tells Drupal to call filevault_load().
 *
 * @param $id
 *   Integer specifying the basic entity id.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   A fully-loaded $basic object or FALSE if it cannot be loaded.
 *
 * @see filevault_load_multiple()
 * @see filevault_menu()
 */
function filevault_load($id = NULL, $reset = FALSE) {
  $ids = (isset($id) ? array($id) : array());
  $files = filevault_load_multiple($ids, $reset);
  return $files ? reset($files) : FALSE;
}

/**
 * Loads multiple basic entities.
 *
 * We only need to pass this request along to entity_load(), which
 * will in turn call the load() method of our entity controller class.
 */
function filevault_load_multiple($ids = FALSE, $conditions = array(), $reset = FALSE) {
  return entity_load('filevault', $ids, $conditions, $reset);
}

/**
 * Implements the uri callback.
 */
function filevault_uri($file) {
  return array(
    'path' => 'filevault/file/' . $file->id,
  );
}
