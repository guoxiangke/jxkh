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

function sbq_center_reservation_manager($centerid) {
//  global $user;
//
//  if(is_object($centerid)){
//    $center = node_load($centerid);
//  }
//  $center = node_load($centerid);
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  module_load_include('inc', 'webform', 'includes/webform.report');
  
  $reservation = sbq_center_reservation_node_by_center($centerid);
  $result = webform_get_submissions(array( 'nid' => $reservation->nid), NULL, 10);
  $result = webform_results_submissions($reservation, NULL, 10);
  echo  ($result);
}
