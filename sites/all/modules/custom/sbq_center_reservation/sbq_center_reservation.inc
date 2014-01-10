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
function sbq_center_opendys_form($form, $formstatus) {

  $header = $part = array(
  );

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

  $form['content'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => array( $part ),
  );
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit your information'),
  );

  return $form;
}

function sbq_center_opendays_form_submmitted($form, $formstatus) {
  return 'success';
}
