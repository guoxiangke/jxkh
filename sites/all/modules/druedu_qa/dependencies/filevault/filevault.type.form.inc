<?php

/**
 * Provides a wrapper on the edit form to add a new entity.
 */
function filevault_add() {

  // Create a basic entity structure to be used and passed to the validation
  // and submission functions.
  $entity = entity_get_controller('filevault')->create();
  return drupal_get_form('filevault_form', $entity);
}

/**
 * Form function to create an filevault entity.
 *
 * The pattern is:
 * - Set up the form for the data that is specific to your
 *   entity: the columns of your base table.
 * - Call on the Field API to pull in the form elements
 *   for fields attached to the entity.
 */
function filevault_form($form, &$form_state, $entity) {

  $form['file'] = array(
    '#type' => 'file',
    '#title' => t('File'),
    '#description' => t('Upload a file'),
  );

  field_attach_form('filevault', $entity, $form, $form_state);

  $form['filevault'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('filevault_edit_delete'),
    '#weight' => 200,
  );

  return $form;
}


/**
 * Validation handler for filevault_add_form form.
 * We pass things straight through to the Field API to handle validation
 * of the attached fields.
 */
function filevault_form_validate($form, &$form_state) {
  field_attach_form_validate('filevault', $form_state['values']['file'], $form, $form_state);

  $file = file_save_upload('file');

  if ($file) {
    if ($file = file_move($file, 'public://')) {

      // All is good. Save file info to the form.
      $form_state['values']['file'] = $file;

      // Update the file status to permanent in the database
      $file->status = 1;
      file_save($file);
    }
    else {
      form_set_error('file', t('Failed to write the uploaded file. Contact an administator'));
    }
  }
  else {
    form_set_error('file', t('No file was uploaded.'));
  }
}

/**
 * Form submit handler: submits basic_add_form information
 */
function filevault_form_submit($form, &$form_state) {
  $entity = $form_state['values']['filevault'];
  $file = $form_state['values']['file'];

  global $user;

  $entity->vid = 0;
  $entity->filename = $file->filename;
  $entity->size = $file->filesize;
  $entity->mime_type = $file->filemime;
  $entity->uri = $file->uri;
  $entity->fid = intval($file->fid);
  $entity->MD5 = "Not implement yet";
  $entity->mime_type = $file->filemime;
  $entity->uid = intval($user->uid);
  $entity->public = TRUE; // not implemented yet
  $entity->public_dir = "/";
  $entity->private_dir = "/";
  $entity->updated = time();

  //field_attach_submit('filevault', $entity, $form, $form_state);
  $entity = filevault_save($entity);
  $form_state['redirect'] = 'filevault/file/' . $entity->id;
}

/**
 * Form deletion handler.
 *
 * @todo: 'Are you sure?' message.
 */
function filevault_edit_delete( $form , &$form_state ) {
  $entity = $form_state['values']['basic_entity'];
  filevault_delete($entity);
  drupal_set_message(t('%filename (ID %id) has been deleted',
    array('%filename' => $entity->filename, '%id' => $entity->basic_id))
  );
  $form_state['redirect'] = 'filevault';
}

/**
 * We save the entity by calling the controller.
 */
function filevault_save(&$entity) {
  return entity_get_controller('filevault')->save($entity);
}

/**
 * Use the controller to delete the entity.
 */
function filevault_delete($entity) {
  entity_get_controller('filevault')->delete($entity);
}
