<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



$types = array( 'curing_guide', 'doctor_legend', 'friend_activities', 'hospital_blacklist', 'illness_diagnosis', 'news' );
$db = db_select('node', 'n')
    ->fields('n', array( 'nid' ))
    ->condition('status', 0)
    ->condition('type', $types, 'in')
    ->range(0, 20)
    ->orderBy('nid', 'ASC')
    ->execute()
    ->fetchAllAssoc('nid');
 
$nids = array_keys($db);
foreach ($nids as $key => $value) {
  $origin = node_load($value);
  $origin->published_at = time();
  $origin->status = 1;
  $result = node_save($origin);
}
if (!$nids) {
  $body = 'aticle is not no published! please disenable cron';
  $subject = 'article aleardy update over';
} else {
  $body = implode(',', $nids) . ' already update';
  $subject = date('Y-m-d H:i:s', time()) . '文章更新';
}
$module = 'test';
$key = 'test';
$to = 'chechao@ylnwt.net';
$from = variable_get('site_mail', 'admin@example.com');
$language = language_default();
$send = TRUE;
$message = array(
    'id' => $module . '_' . $key,
    'module' => $module,
    'key' => $key,
    'to' => $to,
    'from' => isset($from) ? $from : $default_from,
    'language' => $language,
    'params' => array(),
    'send' => FALSE,
    'subject' => $subject,
    'body' => $body,
);
$system = drupal_mail_system($module, $key);
$result = $system->format($message);
$result = $system->mail($message);
file_put_contents('/home/command/1.log', $message);