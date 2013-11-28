<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function sbq_user_relationships_follow_view($display, $account) {
  global $user;
  $accounts = $accounts_view = array();
  switch ($display) {
    case 'default':
      if (in_array(USER_PATIENT_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 3);
      } elseif (in_array(USER_CERTIFIED_DOCTOR_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 1);
      }

      foreach ($accounts as $key => $account) {
        $accounts_view[] = array(
            'user' => user_load($account['user']->uid),
            'relationship_type' => $account[0],
            'relstionship_action' => $account[1],
        );
      }
      return theme('sbq_user_relationships_list', array( 'accounts' => $accounts_view )) . theme('pager');
      break;
    case 'patient':
      if (in_array(USER_PATIENT_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 2);
      } elseif (in_array(USER_CERTIFIED_DOCTOR_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 3);
      }


      foreach ($accounts as $key => $account) {
        $accounts_view[] = array(
            'user' => user_load($account['user']->uid),
            'relationship_type' => $account[0],
            'relstionship_action' => $account[1],
        );
      }
      return theme('sbq_user_relationships_list', array( 'accounts' => $accounts_view )) . theme('pager');
    case 'recommand_doctor':
      $accounts = sbq_user_relationships_recommond($account, USER_CERTIFIED_DOCTOR_RID);
      foreach ($accounts as $viewed) {
        $relatioships = sbq_user_relationships_action_between_user($account, $viewed);
        $relatioships = reset($relatioships);
        $accounts_view[] = array(
            'user' => user_load($viewed->uid),
            'relationship_type' => $relatioships['relationship_type'],
            'relstionship_action' => $relatioships['relationship_action'],
        );
      }
      return theme('sbq_user_relationships_list', array( 'accounts' => $accounts_view )) . theme('pager');
    case 'recommand_patient':
      $accounts = sbq_user_relationships_recommond($account, USER_PATIENT_RID);
      foreach ($accounts as $viewed) {
        $relatioships = sbq_user_relationships_action_between_user($account, $viewed);
        $relatioships = reset($relatioships);
        $accounts_view[] = array(
            'user' => user_load($viewed->uid),
            'relationship_type' => $relatioships['relationship_type'],
            'relstionship_action' => $relatioships['relationship_action'],
        );
      }

      return theme('sbq_user_relationships_list', array( 'accounts' => $accounts_view )) . theme('pager');
    default:
      break;
  }
  return '';
}

/*
 * $type in array('sent', 'received')
 */

function sbq_user_relationship_pending_page($type, $account) {
  if ($type == 'sent') {
    drupal_set_title('发出的请求');
    $options = array(
        'include_user_info' => TRUE,
        'paging' => variable_get('user_relationships_relationships_per_page', 10),
    );
    $relationships = user_relationships_load(array( 'requester_id' => $account->uid, 'approved' => FALSE ), $options);
    $rows = array();
    foreach ($relationships as $relationship) {
      $row = sbq_user_relationships_user_action($relationship, $account);
      $rows[] = array( $row['user']->name, $row[0], $row[1] );
    }
    $output['list'] = array(
        '#theme' => 'table',
        '#rows' => $rows,
        '#header' => array( '用户', '请求关系类型', '操作' ),
        '#empty' => '',
        'attributes' => array( 'class' => array( 'user-relationships-pending-listing-table' ) ),
    );
    $output['pager'] = array(
        '#markup' => theme('pager'),
    );

    return $output;
  } elseif ($type == 'received') {
    drupal_set_title('收到的请求');
    $options = array(
        'include_user_info' => TRUE,
        'paging' => variable_get('user_relationships_relationships_per_page', 10),
    );
    $relationships = user_relationships_load(array( 'requestee_id' => $account->uid, 'approved' => FALSE ), $options);
    dpm($relationships);
    $rows = array();
    foreach ($relationships as $relationship) {
      $row = sbq_user_relationships_user_action($relationship, $account);
      $rows[] = array( $row['user']->name, $row[0], $row[1] );
      //  dpm($row);
    }

    $output['list'] = array(
        '#theme' => 'table',
        '#rows' => $rows,
        '#header' => array( '用户', '请求关系类型', '操作' ),
        '#empty' => '',
        'attributes' => array( 'class' => array( 'user-relationships-pending-listing-table' ) ),
    );
    $output['pager'] = array(
        '#markup' => theme('pager'),
    );

    return $output;
  }
  return 'success';
}

/*
 * @see user_relationships_ui_pending_requested_submit
 */

function sbq_user_relationships_ui_pending_requested_ajax($account, $relationship, $action) {


  switch ($action) {
    case 'cancel':
      if (!user_relationships_ui_check_access('request', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      user_relationships_delete_relationship($relationship, $account, $action);
      if ($_GET['destination']) {
        $commands[] = ajax_command_replace('.' . $_GET['destination'], '取消');
      }
      break;
    case 'approve':
      if (!user_relationships_ui_check_access('approve', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      $relationship->approved = TRUE;
      user_relationships_save_relationship($relationship, $action);
      if ($_GET['destination']) {
        $commands[] = ajax_command_replace('.' . $_GET['destination'], '已同意');
      }
      break;
    case 'disapprove':
      if (!user_relationships_ui_check_access('approve', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      user_relationships_delete_relationship($relationship, $account, $action);

      if ($_GET['destination']) {
        $commands[] = ajax_command_replace('.' . $_GET['destination'], '已拒绝');
      }
      break;
    default:
      break;
  }
  if (isset($commands)) {
    return array( '#type' => 'ajax', '#commands' => $commands );
  }
}
