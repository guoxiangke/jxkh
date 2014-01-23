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
        'order' => array('created', 'DESC'),
    );
    $relationships = user_relationships_load(array( 'requester_id' => $account->uid, 'approved' => FALSE ), $options);

    return theme('sbq_user_relationships_process_status', array( 'type' => 'sent', 'relationships' => $relationships, 'account' => $account ));
  } elseif ($type == 'received') {
    // drupal_set_title('需要出');
    $options = array(
        'include_user_info' => TRUE,
        'paging' => variable_get('user_relationships_relationships_per_page', 20),
        'order' => array('created', 'DESC'),
    );
    $relationships = user_relationships_load(array( 'requestee_id' => $account->uid, 'approved' => FALSE ), $options);

    return theme('sbq_user_relationships_process_status', array( 'type' => 'received', 'relationships' => $relationships, 'account' => $account ));
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
        $commands[] = ajax_command_html('.' . $_GET['destination'], '已同意');
      }
      break;
    case 'disapprove':
      if (!user_relationships_ui_check_access('approve', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      user_relationships_delete_relationship($relationship, $account, $action);

      if ($_GET['destination']) {
        $commands[] = ajax_command_html('.' . $_GET['destination'], '已拒绝');
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
      $commands[] = ajax_command_replace('.' . $token, '<span>已取消</span>');
      return array(
          '#type' => 'ajax',
          '#commands' => $commands );
    }
  }
  ajax_deliver('success');
}

/**
 * use user-roles check_access
 */
function sbq_user_relationships_ui_check_access_by_roles($user, $account, $relationship) {
  // 当前用户为医生
  if (in_array(USER_CERTIFIED_DOCTOR_RID, array_keys($user->roles))) {
    // 被被请求者为医生
    if (in_array(USER_CERTIFIED_DOCTOR_RID, array_keys($account->roles)) && $relationship == FOLLOWER_DOCTOR) {
      return TRUE;
    } // 被被请求者为病人
    elseif (in_array(USER_PATIENT_RID, array_keys($account->roles)) && $relationship == FRIEND_DOCTOR_PATIENT) {
# code...
      return TRUE;
    }
  }// 当前用户为病人
  elseif (in_array(USER_PATIENT_RID, array_keys($user->roles))) {
    //被被请求者为病人
    if (in_array(USER_PATIENT_RID, array_keys($user->roles)) && $relationship == FOLLOWER_PATIENT) {
      return TRUE;
    }//被被请求者为医生
    elseif (in_array(USER_CERTIFIED_DOCTOR_RID, array_keys($account->roles)) && $relationship == FRIEND_DOCTOR_PATIENT) {
# code...
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * @see user_relationships_ui_request_validate
 */
function sbq_user_relationships_ui_request_validate($requester, &$requestee, $rtid) {
  $rtype = user_relationships_type_load($rtid);

  //check that a type has been chosen
  $current_relationships = user_relationships_load(array(
      'between' => array(
          $requester->uid,
          $requestee->uid ) ), array(
      'sort' => 'rtid' ));
  //check for multiple relationships
  if (!variable_get('user_relationships_allow_multiple', TRUE) && count($current_relationships)) {
    form_set_error('rtid', user_relationships_get_message('too_many_relationships'));
    if (isset($_GET['ajax'])) {
      drupal_goto();
    } else {
      return;
    }
  }
  //check user is allowed to request this type
  if (!user_relationships_can_request($requester, $rtype)) {
    // relationship_type_not_allowed
    return FALSE;
  }

  //check user is allowed to receive this type
  if (!user_relationships_can_receive($requestee, $rtype)) {
    return FALSE;
  }

  //check if this request contradicts existing relationships or requests of this type
  //gather rtids of relationships that have already been requested from requester to requestee
  $test_relationships = array();
  foreach ($current_relationships as $key => $value) {
    foreach ($value as $val_rel) {
      //existing two way relationships count no matter the direction
      if (!$val_rel->is_oneway) {
        $test_relationships[$key] = $key;
        continue;
      }
      //if it's one way, but not reciprocal, then it counts no matter the direction
      if (!$val_rel->is_reciprocal) {
        $test_relationships[$key] = $key;
        continue;
      }
      //remaining case is a reciprocal relationship - it counts unless the request is in the opposite direction
      if ($requester->uid == $val_rel->requester_id) {
        $test_relationships[$key] = $key;
      }
    }
  }
  //check if there aren't any available (not yet used) types that can be established
  $select = db_select('user_relationship_types');
  $select->addExpression('COUNT(*)', 'count');
  if ($test_relationships) {
    $select->condition('rtid', $test_relationships, 'NOT IN');
  }
  if (!$select->execute()->fetchField()) {
    // too_many_relationships
    return FALSE;
  }
  //check if desired relationship type is among the unused ones
  elseif (isset($test_relationships[$rtid])) {
    // 'existing_relationship' : 'existing_request';
    return FALSE;
  }

  return TRUE;
}

/**
 * Check access callback
 */
function sbq_user_relationships_ui_check_access($type, $account = NULL, $relationship_type = NULL) {
  global $user;

  if (!is_object($account)) {
    $account = $user;
  }

  if (!is_object($relationship_type)) {
    $relationship_type = user_relationships_type_load($relationship_type);
  }

  if (user_access('administer user relationships')) {
    return TRUE;
  }

  // If the user does not any have permission, deny access.
  if (!user_relationships_can_receive($account)) {
    return FALSE;
  }

  switch ($type) {
    case 'view':
      // First check if it is the current user and if he has view own
      // permission.
      if ($account->uid == $user->uid && user_relationships_user_access('view own @relationship relationships', $relationship_type)) {
        return TRUE;
      }

      // If this is a different user or he doesn't have that permission,
      // check the view all permission.
      if (user_relationships_user_access('view all @relationship relationships', $relationship_type)) {
        return TRUE;
      }
      break;
    case 'approve':
      // Only the administer permission allows to approve, request, delete
      // relationships for other users, which was already checked.
      if ($account->uid == $user->uid && user_relationships_user_access('maintain @relationship relationships', $relationship_type)) {
        return TRUE;
      }
      break;
    case 'request':
      if ($account->uid == $user->uid && user_relationships_can_request($account, $relationship_type)) {
        return TRUE;
      }
      break;
    case 'delete':
      // Do not allow access if this is a oneway relationship requested by another user.
      // if (is_object($relationship_type) && $relationship_type->is_oneway && $relationship_type->requester_id != $user->uid) {
      //   return FALSE;
      // }
      if ($account->uid == $user->uid && user_relationships_user_access('delete @relationship relationships', $relationship_type)) {
        return TRUE;
      }
      break;
  }
  return FALSE;
}
