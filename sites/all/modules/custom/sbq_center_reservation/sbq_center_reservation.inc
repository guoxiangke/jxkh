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
  $header = $part = array();
  //variable_delete('center_reservation_23277_settings');
  $settings = sbq_center_reservation_get_settings($center);
  // foreach (array( 'monday' => '星期一', 'tuesday' => '星期二', 'wednesday' => '星期三', 'thursday' => '星期四', 'friday' => '星期五', 'saturday' => '星期六', 'sunday' => '星期日', ) as $key => $item) {
  //   $header[$key] = $item;
  //   $default = array();
  //   if (isset($settings['opendays'][$key]['a']) && $settings['opendays'][$key]['a']) {
  //     $default[] = 'a';
  //   }
  //   if (isset($settings['opendays'][$key]['p']) && $settings['opendays'][$key]['p']) {
  //     $default[] = 'p';
  //   }
  //   $part[$key] = array(
  //     '#type' => 'checkboxes',
  //     '#default_value' => $default,
  //     '#options' => array(
  //       'a' => '上午',
  //       'p' => '下午'
  //     )
  //   );
  // }
  // $form['centerid'] = array(
  //   '#type' => 'hidden',
  //   '#value' => $center->nid
  // )

  $form['content'] = array(
      '#markup' => theme('sbq_center_reservation_settings', array( 'settings' => $settings['opendays'], 'centerid' => $center->nid )),
  );
  //$form['opendays'] = $part;

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

//  $data = array();
//  foreach ($form['opendays'] as $key => $value) {
//    if (strpos($key, '#') !== 0) {
//      $data[$key] = $form_status['values'][$key];
//    }
//  }
  $settings = sbq_center_reservation_get_settings(0);

  $input = $form_status['input'];


  foreach ($settings['opendays'] as $key => $values) {
    if (in_array($key, array_keys($input))) {
      $item = array(
          'a' => isset($input[$key]['a']) ? 'a' : 0,
          'p' => isset($input[$key]['p']) ? 'p' : 0,
      );
    } else {
      $item = array(
          'a' => 0, 'p' => 0,
      );
    }
    $data[$key] = $item;
  }
  $seri = array( 'opendays' => $data, 'numofday' => 10 );
  variable_set('center_reservation_' . $input['centerid'] . '_settings', serialize($seri));
  drupal_set_message('设置成功', 'status');
}

function sbq_center_reservation_manage($center, $reservation, $action) {
  switch ($action) {
    case 'accept':
      if ($reservation->field_reservation_status['und'][0]['value'] == SBQ_CENTER_RESERVATION_STATUS_SUBMMIT) {
        $reservation->field_reservation_status['und'][0]['value'] = SBQ_CENTER_RESERVATION_STATUS_ACCEPT;

        if (!sbq_center_reservation_status($reservation->field_reservation_time['und'][0]['value'], $center->nid)) {
          return '操作失败，这个时间段已经约满，' . l('点击返回', "center/{$center->nid}/reservation/manage");
        }
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


  return '操作成功，' . l('点击返回', "center/{$center->nid}/reservation/manage");
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
      'og_group_ref' => array( 'und' => array( array( 'target_id' => $center->nid ) ) ),
      'language' => LANGUAGE_NONE
  );
  drupal_set_title(t('Create @name', array( '@name' => $types[SBQ_CENTER_RESERVATION_NODE_TYPE]->name )), PASS_THROUGH);
  $param = drupal_get_query_parameters();
  
  if (isset($param['date'])) {
    $node['field_reservation_time']['und'][0]['value'] = $param['date'];
  }else{
    drupal_goto('center/'.$center->nid.'/index');
  }
  if(!sbq_center_reservation_status($node['field_reservation_time']['und'][0]['value'], $center->nid)){
    drupal_set_message('该日期已经约满,请重新选择日期！', 'warning');
    drupal_goto('center/'.$center->nid.'/index');
  }
  return drupal_get_form('sbq_center_reservation_node_form', (object) $node);
}
