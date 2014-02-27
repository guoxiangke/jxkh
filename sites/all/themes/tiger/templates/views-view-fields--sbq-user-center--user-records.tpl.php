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
  foreach ($fields as $id => $field) {
    $$id = $field->wrapper_prefix.$field->label_html.$field->content.$field->wrapper_suffix;
    if (!empty($field->separator)){
      $$id = $field->separator.$$id;
    }
  }
?>

<div class="sbq_item">
  <div class="sbq_head">
    <div class="sbq_title">
      <?php if ($field_grow_records_video || $field_grow_records_voice):?>
      <span>
        <?php if ($field_grow_records_video):?>
        <i class="sbq_video"></i>
        <?php if ($field_grow_records_voice):?>
        <?php endif; ?>
        <i class="sbq_record"></i>
        <?php endif; ?>
      </span>
      <?php endif; ?>
      <?php print $title; ?>
    </div>
    <div class="sbq_time"><?php print $created; ?></div>
  </div>
  <?php if ($body):?>
  <div class="sbq_text"><?php print $body; ?></div>
  <?php endif; ?>
  <?php if ($field_grow_records_img):?>
  <div class="sbq_img">
    <?php print $field_grow_records_img; ?>
  </div>
  <?php endif; ?>
</div>
