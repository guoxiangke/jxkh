<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function sbq_user_relationships_follow_view($display, $account) {
  switch ($display) {
    case 'default':
      $build = theme('sbq_user_relationships_list', array( 'accounts' => sbq_user_relationships_follow($account, USER_CERTIFIED_DOCTOR_RID) ));
      return $build .= theme('pager');
      break;
    case 'patient':
      $build = theme('sbq_user_relationships_list', array( 'accounts' => sbq_user_relationships_follow($account, USER_PATIENT_RID) ));
      return $build .= theme('pager');
    case 'recommand_doctor':
      $build = theme('sbq_user_relationships_list', array( 'accounts' => sbq_user_relationships_recommond($account, USER_CERTIFIED_DOCTOR_RID) ));
      return $build .= theme('pager');
    case 'recommand_patient':
      $build = theme('sbq_user_relationships_list', array( 'accounts' => sbq_user_relationships_recommond($account, USER_PATIENT_RID) ));
      return $build .= theme('pager');

    default:
      break;
  }
  return '';
}
