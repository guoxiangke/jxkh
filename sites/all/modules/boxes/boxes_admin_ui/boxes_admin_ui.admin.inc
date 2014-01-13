<?php

/**
 * @file
 * Boxes Admin Page
 */

/**
 * Main page callback on the box type
 */
function boxes_admin_ui_admin_page() {
  $field_ui = module_exists('field_ui');
  $rows = array();
  $i = 0;

  foreach (boxes_get_types() as $box_type) {
    $row = array();
    $row[] = array('data' => $box_type->getLabel());
    if (method_exists($box_type, 'getExportStatus')) {
      $export_status = $box_type->getExportStatus();
    }
    else {
      $export_status = 'Normal';
    }
    $row[] = array('data' => $export_status);
    // Edit and delete buttons
    if ($box_type->isEditable()) {
      $row[] = array('data' => l(t('edit'), 'admin/structure/block-types/manage/' . $box_type->buildURL() . '/edit'));
      switch ($export_status) {
        case 'Normal':
          $row[] = array('data' => l(t('delete'), 'admin/structure/block-types/manage/' . $box_type->buildURL() . '/delete'));
          break;
        case 'Overridden':
          $row[] = array('data' => l(t('revert'), 'admin/structure/block-types/manage/' . $box_type->buildURL() . '/delete'));
          break;
        case 'Default':
          $row[] = array();
          break;
      }
    }

    if ($field_ui) {
      // Manage fields.
      $row[] = array('data' => l(t('manage fields'), 'admin/structure/block-types/manage/' . $box_type->buildURL() . '/fields'));

      // Display fields.
      $row[] = array('data' => l(t('manage display'), 'admin/structure/block-types/manage/' . $box_type->buildURL() . '/display'));
    }
    //creative way to setup sorting rows; add number to prevent dual keys
    $rows[str_replace(' ', '', $box_type->getLabel()) . '_' . $i] = $row;
  }
  ksort($rows);

  $header = array(t('Name'), t('Status'), array('data' => t('Operations'), 'colspan' => $field_ui ? '6' : '4'));

  $build['box_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no Block Types Available'),
  );
  return $build;
}

/**
 * Generates the bean type editing form.
 */
function boxes_admin_ui_type_form($form, &$form_state, $box_type = NULL) {
  $form['new'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );
  // If bean_type is null then load an empty one.
  if (is_null($box_type)) {
    $plugin_info = _boxes_admin_default_plugin();
    $plugin_info['name'] = '';

    $box_type = new BoxCustom($plugin_info);
  }
  elseif (!method_exists($box_type, 'getExportStatus') || $box_type->getExportStatus() == 'Normal') {
    $form['new'] = array(
      '#type' => 'value',
      '#value' => FALSE,
    );
  }

  $disabled = !$box_type->isEditable();

  if ($disabled) {
    drupal_set_message(t('This Block Type can not be edited'));
  }
  $form['box_type'] = array(
    '#type' => 'value',
    '#value' => $box_type,
  );

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $box_type->getLabel(),
    '#description' => t('The human-readable name of this block type.'),
    '#required' => TRUE,
    '#size' => 30,
    '#disabled' => $disabled,
  );

  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#default_value' => $box_type->getDescription(),
    '#description' => t('The description of this block type.'),
    '#disabled' => $disabled,
  );

  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($box_type->type) ? $box_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'boxes_type_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this block type. It must only contain lowercase letters, numbers, and underscores.'),
    '#disabled' => $disabled,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Block type'),
    '#weight' => 40,
    '#disabled' => $disabled,
  );

  // This is a new bean type.
  if (isset($plugin_info)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Block type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('boxes_type_form_submit'),
      '#disabled' => $disabled,
    );
  }
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function boxes_admin_ui_type_form_submit(&$form, &$form_state) {
  $box_type = $form_state['values']['box_type'];
  $box_type->type = $form_state['values']['name'];
  $box_type->setLabel($form_state['values']['label']);
  $box_type->setDescription($form_state['values']['description']);
  $box_type->save($form_state['values']['new']);
  cache_clear_all('boxes_plugins', 'cache');

  $form_state['redirect'] = 'admin/structure/block-types';
  ctools_include('export');
}

/**
 * Form API submit callback for the delete button.
 */
function boxes_admin_ui_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/block-types/manage/' . $form_state['box_type']->type . '/delete';
}

/**
 * Menu callback; delete a single content type.
 */
function boxes_admin_ui_type_delete_confirm($form, &$form_state, $type) {
  $form['type'] = array('#type' => 'value', '#value' => $type);
  $form['name'] = array('#type' => 'value', '#value' => $type->getLabel());
  $caption = '';
  if (!method_exists($type, 'getExportStatus') || $type->getExportStatus() == 'Normal') {
    $message = t('Are you sure you want to delete the block type %type?', array('%type' => $type->getLabel()));
    $num_boxes = db_query("SELECT COUNT(*) FROM {box} WHERE type = :type", array(':type' => $type->type))->fetchField();
    if ($num_boxes) {
      $caption .= '<p>' . format_plural($num_boxes, '%type is used by 1 block on your site. If you remove this block type, you will not be able to edit the %type blocks and it may not display correctly.', '%type is used by @count pieces of content on your site. If you remove %type, you will not be able to edit the %type content and it may not display correctly.', array('%type' => $type->getLabel())) . '</p>';
    }
    $action = t('Delete');
  }
  else {
    $message = t('Are you sure you want to revert the block type %type?', array('%type' => $type->getLabel()));
    $action = t('Revert');
  }
  $caption .= '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $message, 'admin/structure/block-types', $caption, $action);
}

function boxes_admin_ui_type_delete_confirm_submit($form, &$form_state) {
  $form_state['values']['type']->delete();
  $form_state['redirect'] = 'admin/structure/block-types';
}
