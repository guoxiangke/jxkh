<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function sbq_center_reservation($sbq_center, $reservation) {
  if (in_array($reservation, array( SBQ_CENTER_RESERVATION_TYPE_OUTPATIMENT, SBQ_CENTER_RESERVATION_TYPE_PHONE ))) {
    $form = drupal_get_form('sbq_center_reservation_form', $reservation);
  }
  dpm($form);
  return isset($form) ? $form : '';
}
