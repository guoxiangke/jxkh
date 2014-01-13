<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */// dpm($row->field_field_tags);
?>
<ul>
<?php
  foreach ($row->field_field_tags as $key => $tag) {
    $tag_title = trim($tag['rendered']['#title']);
    $tid = trim($tag['raw']['tid']);
    if (strlen($tag_title)>0 && $tid>0) {
      $tag_count = 1;
      $nids = taxonomy_select_nodes($tid, FALSE);
      $tag_count = count($nids);
      $output = '<li>'
        . '<a href="'.url('questions/tagged/').'?field_tags_tid='.$tag_title.'">'
        . '<span class="sbq_tit">'.$tag_title.'</span>'
        . '<span class="sbq_num">'.$tag_count.'</span>'
        . '</a>';
      print $output;
    }
  }
?>
</ul>
