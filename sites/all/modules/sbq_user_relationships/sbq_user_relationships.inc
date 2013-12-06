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

function sbq_user_relationship_pending_page($type, $account = NULL) {
  global $user;
  if ($account) {
    $account = $user;
  }
  if ($type == 'sent') {
    // drupal_set_title('发出的请求');
    $options = array(
        'include_user_info' => TRUE,
        'paging' => variable_get('user_relationships_relationships_per_page', 20),
    );
    $relationships = user_relationships_load(array( 'requester_id' => $account->uid, 'approved' => FALSE ), $options);
   
    return theme('sbq_user_relationships_process_status', array( 'type' => 'sent', 'relationships' => $relationships,'account'=> $account));
  } elseif ($type == 'received') {
    // drupal_set_title('需要出');
    $options = array(
        'include_user_info' => TRUE,
        'paging' => variable_get('user_relationships_relationships_per_page', 20),
    );
    $relationships = user_relationships_load(array( 'requestee_id' => $account->uid, 'approved' => FALSE ), $options);
    
    return theme('sbq_user_relationships_process_status', array( 'type' => 'received', 'relationships' => $relationships,'account'=> $account));
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
        $commands[] = ajax_command_replace('.' . $_GET['destination'], '<span>已取消</span>');
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
        $commands[] = ajax_command_html('.' . $_GET['destination'], '<span>已同意<span>');
      }
      break;
    case 'disapprove':
      if (!user_relationships_ui_check_access('approve', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      user_relationships_delete_relationship($relationship, $account, $action);

      if ($_GET['destination']) {
        $commands[] = ajax_command_html('.' . $_GET['destination'], '<span>已拒绝</span>');
      }
      break;
    default:
      break;
  }
  if (isset($commands)) {
    return array( '#type' => 'ajax', '#commands' => $commands );
  }
}

/**
 * Process relationship request.
 */
function sbq_user_relationships_ui_request_ajax($viewer_id, $rid, $viewed_id) {
  //#578372 leave all form values in the object for other functions to use
  $relationship = new stdClass;
  $relationship->requester = user_load($viewer_id);
  $relationship->requestee = user_load($viewed_id);
  $relationship->type = user_relationships_type_load($rid);
  $relationship = user_relationships_request_relationship($relationship);

  if ($relationship === FALSE || !$relationship) {
    ajax_deliver('error');
  }
  if ($relationship->type->rtid == FRIEND_DOCTOR_PATIENT) {
    $replace = '<span>已发送请求</span>';
  } else {
    $replace = '<span>已关注</span>';
  }
  $path = $_GET['q'];
  if ($position = strpos($path, 'destination=')) {
    if ($token = substr($path, $position, strlen($path))) {
      $token = str_replace('destination=', '', $token);
      $commands[] = ajax_command_replace('.' . $token, $replace);
      return array( '#type' => 'ajax', '#commands' => $commands );
    }
  }
  ajax_deliver('success');
}

/**
 * Remove relationship request.
 */
function sbq_user_relationships_ui_remove_ajax($viewer_id, $rid, $viewd_id) {
  $user = user_load($viewer_id);
  $relationship = user_relationships_load($rid);
  if (!user_relationships_ui_check_access('delete', NULL, $relationship)) {
    drupal_access_denied();
    exit();
  }
  if (!user_relationships_load($rid)) {
    sbq_commons_ajax_response('success', '找不到此关系！', NULL, render($html));
  }
  user_relationships_delete_relationship($relationship, $user);
//  drupal_set_message(user_relationships_get_message('removed', $relationship));
//  $html = sbq_commons_user_relationship_view(user_load($viewd_id), NULL, NULL);
//  sbq_commons_ajax_response('success', 'success', NULL, render($html));
  $path = $_GET['q'];

  if ($position = strpos($path, 'destination=')) {
    if ($token = substr($path, $position, strlen($path))) {
      $token = str_replace('destination=', '', $token);
      $commands[] = ajax_command_replace('.' . $token, '<span>已移除</span>');
      return array(
          '#type' => 'ajax',
          '#commands' => $commands );
    }
  }
  ajax_deliver('success');
}
