<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
  /*
Crystal:
$field->content should not contain any markup.
If the variable contains markup, edit the View, go to "FORMAT", "Show:" and click "Settings", and uncheck "Provide default field wrapper elements" to remove all the generated markup for this View.
*/ //to see the fileds.
?>
<?php
  $status = '';
  foreach ($fields as $id => $field) {
    $$id = $field->wrapper_prefix.$field->label_html.$field->content.$field->wrapper_suffix;
    if (!empty($field->separator)){
      $$id = $field->separator.$$id;
    }
    if ($id == 'field_reservation_status') {
      if (trim($field->content) == '0') {
        $status = '<span class="submitted">已提交</span>';
      } elseif (trim($field->content) == '1') {
        $status = '<span class="pass">预约成功</span>';
      } elseif (trim($field->content) == '2') {
        $status = '<span class="refused">预约失败</span>';
      }
    }
    if ($id == 'php') {
      $option = $field->content;
    }
    if ($id == 'body') {
      $body_content = $field->content;
    }
  }
  $options = $status.$option;

?>

<tr class="odd">
  <td><?php print $nid; ?></td>
  <td><?php print $field_real_name; ?></td>
  <td><?php print $field_phone; ?></td>
  <td><?php print $field_reservation_time; ?></td>
  <td><?php print $options; ?></td>
</tr>
<tr class="even">
  <td colspan="5"><strong>病情简介：</strong><?php print $body_content; ?></td>
</tr>
