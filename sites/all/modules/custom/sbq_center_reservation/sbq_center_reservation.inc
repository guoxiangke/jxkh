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
      if ($reservation->field_reservation_status['und'][0]['value'] == SBQ_CENTER_RESERVATION_STATUS_SUBMMIT) {
        $reservation->field_reservation_status['und'][0]['value'] = SBQ_CENTER_RESERVATION_STATUS_ACCEPT;
        node_save($reservation);
        foreach (module_implements('reservation_status_alter') as $key => $value) {
          module_invoke($value, 'reservation_status_alter', $reservation);
        }
      }
      break;

    case 'ignore':
      $reservation->field_reservation_status['und'][0]['value'] = SBQ_CENTER_RESERVATION_STATUS_IGNORE;
      node_save($reservation);
      break;
  }
  return 'success';
}

function sbq_center_reservation_created($center, $account = NULL) {
  if (FALSE !== is_null($account)) {
    global $user;
    $account = $user;
  }
  module_load_include('inc', 'node', 'node.pages');
  $types = node_type_get_types();
  $node = array(
      'uid' => $account->uid,
      'name' => (isset($account->name) ? $account->name : ''),
      'type' => SBQ_CENTER_RESERVATION_NODE_TYPE,
      'og_group_ref' => array('und'=>array(array('target_id'=>$center->nid))),
      'language' => LANGUAGE_NONE
  );
  drupal_set_title(t('Create @name', array( '@name' => $types[SBQ_CENTER_RESERVATION_NODE_TYPE]->name )), PASS_THROUGH);
  return drupal_get_form('sbq_center_reservation_node_form', (object)$node);
}
