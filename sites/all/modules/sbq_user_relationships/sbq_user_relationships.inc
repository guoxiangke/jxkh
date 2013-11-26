<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function sbq_user_relationships_follow_view($display, $account) {
  global $user;

  switch ($display) {
    case 'default':
      if (in_array(USER_PATIENT_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 3);
      } elseif (in_array(USER_CERTIFIED_DOCTOR_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 1);
      }

      $accounts_view = array();
      foreach ($accounts as $key => $account) {
        $accounts_view[] = array(
            'user' => user_load($account['user']->uid),
            'relationship_type' => $account[0],
            'relstionship_action' => $account[1],
        );
      }
      return theme('sbq_user_relationships_list', array( 'accounts' => $accounts_view )). theme('pager');
      break;
    case 'patient':
      if (in_array(USER_PATIENT_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 2);
      } elseif (in_array(USER_CERTIFIED_DOCTOR_RID, array_keys($account->roles))) {
        $accounts = sbq_user_relstionships_users($account, 3);
      }

      $accounts_view = array();
      foreach ($accounts as $key => $account) {
        $accounts_view[] = array(
            'user' => user_load($account['user']->uid),
            'relationship_type' => $account[0],
            'relstionship_action' => $account[1],
        );
      }
      return theme('sbq_user_relationships_list', array( 'accounts' => $accounts_view )).theme('pager');
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
