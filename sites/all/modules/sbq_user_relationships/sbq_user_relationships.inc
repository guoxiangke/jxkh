<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function sbq_user_relationships_follow_view($display) {
  global $user;
  switch ($display) {
    case 'default':
      return sbq_user_relationships_follow($user, USER_CERTIFIED_DOCTOR_RID);
      break;
    case 'patient':
      return sbq_user_relationships_follow($user, USER_PATIENT_RID);
    default:
      break;
  }
  return '';
}
