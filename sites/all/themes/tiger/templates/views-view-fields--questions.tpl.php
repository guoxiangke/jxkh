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
*/
?>

<?php /**foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
  <?php print $field->wrapper_suffix; ?>
<?php endforeach; */?>

<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php $$id = $field->separator; ?>
  <?php endif; ?>

  <?php $$id = $field->wrapper_prefix.$field->label_html.$field->content.$field->wrapper_suffix; ?>
<?php endforeach; ?>
<?php $node = node_load($nid); ?>
<div class="sbq_question_item">
  <h2 class="sbq_title"><?php print $title; ?></h2>
  <div class="votes"><a href="/question/<?php print $nid; ?>"><span class="count"><?php print $fields['field_computed_answers']->content; ?></span></a></div>
  <div class="sbq_content">
    <div class="sbq_user_name"><?php print $name; ?></div>
    <div class="sbq_text"><?php print $body; ?></div>
    <div class="sbq_reply_actions">
      <ul>
        <li class="sbq_follow_btn"><?php print flag_create_link('follow', $nid); ?></li>
        <?php if ($node->comment_count > 0) {?>
          <li class="sbq_reply_btn">回复(<?php print $node->comment_count; ?>)</li>
        <?php }?>
        <li><?php print $published_at; ?></li>
        <?php if(!empty($edit_node)): ?>
        <li class="sbq_edit"><?php print $edit_node; ?></li>
        <?php endif;?>
        <?php if(!empty($delete_node)): ?>
        <li class="sbq_delete"><?php print $delete_node; ?></li>
        <?php endif;?>
      </ul>
    </div>
  </div>
</div>
