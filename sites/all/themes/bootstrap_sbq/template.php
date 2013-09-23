<?php

/**
 * @file template.php
 */
function _bootstrap_content_col_md($columns = 1) {
  $class = FALSE;
  
  switch($columns) {
    case 1:
      $class = 'span12';
      break;
    case 2:
      $class = 'span8';
      break;
    case 3:
      $class = 'span6';
      break;
  }
  
  return $class;
}
