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
  $has_image = FALSE;
  if (isset($field_image)) {
    $has_image = TRUE;
  }
?>

<div class="sbq_item">
  <?php if($has_image): ?>
  <div class="sbq_img"><?php print $field_image; ?></div>
  <div class="sbq_content">
  <?php endif;?>
    <h2 class="sbq_title"><?php print $title; ?></h2>
    <div class="sbq_text"><?php print $body; ?></div>
    <div class="sbq_reply_actions">
      <ul>
        <li><?php print $comment_count; ?></li>
        <li><?php print $created; ?></li>
        <?php if(!empty($edit_node)): ?>
        <li class="edit"><?php print $edit_node; ?></li>
        <?php endif;?>
        <?php if(!empty($delete_node)): ?>
        <li class="delete"><?php print $delete_node; ?></li>
        <?php endif;?>
      </ul>
    </div>
  <?php if($has_image): ?>
  </div>
  <?php endif;?>
</div>
