<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * set opendays form
 * @param type $form
 * @param type $formstatus
 * @return string
 */
function sbq_center_opendays_form($form, $form_status, $center) {
  dpm($center);
  $header = $part = array();
  foreach (array( 'monday' => '星期一', 'tuesday' => '星期二', 'wednesday' => '星期三', 'thursday' => '星期四', 'friday' => '星期五', 'saturday' => '星期六', 'sunday' => '星期日', ) as $key => $item) {
    $header[$key] = $item;

    $part[$key] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'a' => '上午',
            'b' => '下午'
        )
    );
  }
  $form['centerid'] = array(
      '#type' => 'hidden',
      '#value' => $center->nid
  );
  $form['content'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
  );
  $form['opendays'] = $part;

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('提交'),
  );

  return $form;
}

/**
 * form sbq center ipenda
 * @param type $form
 * @param type $form_status
 */
function sbq_center_opendays_form_submit($form, $form_status) {
  $data = array();
  foreach ($form['opendays'] as $key => $value) {
    if (strpos($key, '#') !== 0) {
      $data[$key] = $form_status['values'][$key];
    }
  }

  $seri = array( 'opendays' => $data, 'numofday' => 10 );

  variable_set('center_reservation_' . $form_status['values']['centerid'] . '_settings', serialize($seri));
}

function sbq_center_reservation_manage($center, $reservation, $action) {
  switch ($action) {
    case 'accept':
      $reservation->field_reservation_status['und'][0]['value'] = SBQ_CENTER_RESERVATION_STATUS_ACCEPT;
      node_save($reservation);

      break;

    case 'ignore':
      $reservation->field_reservation_status['und'][0]['value'] = SBQ_CENTER_RESERVATION_STATUS_IGNORE;
      node_save($reservation);
      break;
  }
  return 'success';
}
