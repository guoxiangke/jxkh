<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function sbq_center_reservation($sbq_center, $reservation) {
  if (in_array($reservation, array( SBQ_CENTER_RESERVATION_TYPE_OUTPATIMENT, SBQ_CENTER_RESERVATION_TYPE_PHONE ))) {
    $form = sbq_center_reservation_sheet($reservation);
  }
  return isset($form) ? $form : '';
}

function sbq_center_reservation_manage($centerid) {
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  module_load_include('inc', 'webform', 'includes/webform.report');
  $reservation_node = sbq_center_reservation_node_by_center($centerid);
  $result = sbq_center_reservation_get_submissions(array( 'nid' => $reservation_node->nid ), NULL, 10, 'FALSE');
  $reservations = sbq_center_reservation_render($reservation_node, $result, NULL, 'html', TRUE);
  $header = webform_component_list($reservation_node);
  return theme('sbq_center_reservation', array( 'reservations' => $reservations, 'header' => $header, 'manage' => TRUE, 'nid' => $centerid )) . theme('pager');
}

function sbq_center_reservation_action($centerid, $sid, $action) {
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  module_load_include('inc', 'webform', 'includes/webform.report');
  $reservation_node = sbq_center_reservation_node_by_center($centerid);
  $submission = webform_get_submission($reservation_node->nid, $sid);
  switch ($action) {
    case 'accept':
      if (!empty($submission)) {
        db_update('webform_submitted_data')->fields(array( 'data' => SBQ_CENTER_RESERVATION_STATUS_REQ ))
            ->condition('nid', $reservation_node->nid)
            ->condition('sid', $sid)
            ->condition('cid', sbq_center_reservation_field_keys('sbq_center_status'))
            ->execute();
        foreach (module_implements('webform_submission_update') as $key => $value) {
          $submission->is_accept = TRUE;
          module_invoke($value, 'webform_submission_update', $reservation_node, $submission);
        }

        return 'success';
      }
      break;

    case 'ignore':
      if (!empty($submission)) {
        db_update('webform_submitted_data')->fields(array( 'data' => SBQ_CENTER_RESERVATION_STATUS_IGN ))
            ->condition('nid', $reservation_node->nid)
            ->condition('sid', $sid)
            ->condition('cid', sbq_center_reservation_field_keys('sbq_center_status'))
            ->execute();
        return 'success';
      }
      break;
  }

//  if ($submission) {
//    $values = array();
//    foreach ($submission->data as $key => $value) {
//      if ($key == 1) {
//        $values[$key][0] = $value['value'][0];
//      } else {
//        $values[$key] = $value['value'][0];
//      }
//    }
//
//    return sbq_center_reservation_update($reservation_node, $sid, $values);
//  }
  return 'false';
}
