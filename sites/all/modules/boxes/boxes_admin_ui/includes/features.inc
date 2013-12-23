<?php

/**
 * @file
 * Features module hooks
 */

/**
 * Implements hook_features_pipe_MODULE_alter().
 */
function boxes_admin_ui_features_pipe_bean_type_alter(&$pipe, $data, $export) {
  if (isset($export['features']['box_type'])) {
    foreach ($export['features']['box_type'] as $type_name) {
      $fields = field_info_instances('box', $type_name);
      foreach ($fields as $name => $field) {
        $pipe['field'][] = "box-{$field['bundle']}-{$field['field_name']}";
      }
    }
  }
}
