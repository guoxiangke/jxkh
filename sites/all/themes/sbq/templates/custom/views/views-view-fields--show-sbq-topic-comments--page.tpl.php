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
 // dpm($fields;
  // foreach ($fields as $id => $field) {
  //   $$id = $field->wrapper_prefix.$field->label_html.$field->content.$field->wrapper_suffix;
  //   if (!empty($field->separator)){
  //     $$id = $field->separator.$$id;
  //   }    
  // }
?>
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>

  <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>
<?php
  $cid = $fields['cid']->raw;
  if (user_access('post comments')) {
    // dpm($fields);
    $node = node_load($fields['nid_1']->raw);

    include_once drupal_get_path('module', 'comment').'/comment.pages.inc';
    $comment = comment_reply($node, $cid);
    $comment_form = $comment['comment_form'];
    $comment_form['#action'] = "/comment/reply/{$node->nid}/{$cid}";
    print render($comment_form);
  }
  if($id == 'nid_1') {
     $replys = sbq_comment_get_replys($cid);     
      ?>
      <div class="sbq_topic_replay_warpper" id="sbq_topic_replay_warpper_<?php echo $cid;?>">
      <?php
      if(count($replys))
      foreach ($replys as $key => $reply) {
        $pid = $reply->pid;
        print sbq_comment_print_comment($pid);
      }
      ?>
      </div> 
     <?php 

  }
?>