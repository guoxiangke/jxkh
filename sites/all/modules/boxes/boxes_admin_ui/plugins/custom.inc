<?php

/**
 * @file
 * Box ctools plugin
 */

/**
 * DO NOT USE THIS BOX.  ONLY USED FOR THE UI PLUGINS
 */
class BoxCustom extends BoxPlugin {
  /**
   * Delete the record from the database.
   */
  public function delete() {
    // Delete all boxes belonging to this box type if we are removing
    // the actual box.
    if ($this->getExportStatus() == 'Normal') {
      db_delete('box')
      ->condition('type', $this->type)
      ->execute();
    }
    db_delete('box_type')
    ->condition('name', $this->type)
    ->execute();
    field_attach_delete_bundle('box', $this->type);
    drupal_flush_all_caches();
  }

  /**
   * Save the record to the database
   */
  public function save($new = FALSE) {
    $box_type = array(
      'name' => $this->type,
      'label' => $this->getLabel(),
      'description' => $this->getDescription(),
    );

    $primary_key = $new == FALSE ? 'name' : array();
    drupal_write_record('box_type', $box_type, $primary_key);
    drupal_static_reset('boxes_admin_ui_get_types');

    boxes_reset();
  }

  /**
   * Get the export status
   */
  public function getExportStatus() {
    return $this->plugin_info['export_status'];
  }

  /**
   * Set the label.
   *
   * @param label
   */
  public function setLabel($label) {
    $this->plugin_info['label'] = $label;
  }

  /**
   * Set the description.
   *
   * @param description
   */
  public function setDescription($description) {
    $this->plugin_info['description'] = $description;
  }
}
