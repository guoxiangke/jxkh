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
  if(isset($ops))
  $accept_link = $ops;
  $node = node_load($nid);//answer node /q-node
  global $base_url, $user;
  $share_a_node = $base_url.'/node/'.$row->nid.'/share/'.$user->uid.'/nojs';
  $comments_per_page = 4;

  //field_ask_anonymous
  if($fields['field_ask_anonymous']->content == 1) {
    $name = '<a href="#">匿名提问</a>';
  }
  //user pic default
  if(!strlen($picture)) {
    $account = user_load($fields['nid']->raw);
    $picture = variable_get('user_picture_default', '');
    $picture = theme('image_style',array('style_name' => 'profile_small', 'path' => $picture));
  }
?>
<?php if(!$og_group_ref):?>
<div class="sbq_tags">
  <?php if(isset($field_tags)) print $field_tags; ?>
</div>
<?php endif?>
<div class="sbq_question">
  <div class="sbq_content">
    <?php if($node->type == 'question'):?>
    <h2 class="sbq_title"><?php print trim($title); ?></h2>
    <?php endif?>
    <div class="sbq_text">
      <?php print $body; ?>
    </div>
    <div class="sbq_reply_actions">
      <ul>
        <li><?php print $created; ?></li>
        <li class="sbq_reply_btn">
          <?php if (!$user->uid) {?>
            <?php if ($node->comment_count == 0) {?>
              <a href="/user/login?destination=question/<?php print $nid; ?>" class="sbq_add_reply_btn anonymous_no_comment ">添加评论</a>
            <?php } else {?>
              <a href="#" class="sbq_add_reply_btn anonymous_comments"><?php print $node->comment_count; ?>条评论</a>
            <?php }?>
          <?php } else {?>
            <a href="#" class="sbq_add_reply_btn login_user">
              <?php if ($node->comment_count == 0) {?>
              添加评论
            <?php } else {?>
              <?php print $node->comment_count; ?>条评论
            <?php }?>
            </a>
          <?php }?>
        </li>
        <?php if(!empty($edit_node)): ?>
        <li class="edit"><?php print $edit_node; ?></li>
        <?php endif;?>
        <?php if(!empty($delete_node)): ?>
        <li class="delete"><?php print $delete_node; ?></li>
        <?php endif;?>
      </ul>
    </div>
    <?php
      $q_comments = comment_get_thread($node, COMMENT_MODE_FLAT, $comments_per_page);
      $comments_count = $node->comment_count;
      $warp_add_class = '';
      if ($comments_count == 0) {
        $warp_add_class = 'no_reply';
      }
    ?>
    <div class="sbq_reply_wrap <?php print $warp_add_class ?>">
      <div id="comments-<?php print $nid ?>" class="sbq_reply_list">
        <ul>
          <?php
            foreach ($q_comments as $key => $value) {
              $q_comment = comment_load($value);
              $account = user_load($q_comment->uid);
              $qc_name = theme('username', array('account' => $account));
              $qc_picture = theme('user_picture', array('account' =>$account));
              $comment_date = format_date($q_comment->changed, 'short');
              $comment_body = $q_comment->comment_body['und'][0]['safe_value'];
          ?>
          <li>
            <div class="sbq_user_pic"><?php print $qc_picture; ?></div>
            <div class="sbq_reply_list_content">
              <div class="sbq_user_name"><?php print $qc_name; ?></div>
              <div class="sbq_text"><?php print $comment_body; ?></div>
              <div class="sbq_date"><?php print $comment_date; ?></div>
            </div>
          </li>
          <?php
            } // end of foreach
          ?>
        </ul>
      </div>
      <?php if ($node->comment_count > $comments_per_page) {?>
        <div class="sbq_all_reply_btn"><a href="#" nid="<?php print $nid; ?>">显示全部评论</a></div>
      <?php } // end of if ?>
      <?php
      if(user_is_logged_in())
      foreach ( $view->result as $q_a_item) {//both for question & answers.
       if(isset($q_a_item->comments) && $row->nid==$q_a_item->comments['#form']['nid']['#value']){
         ?>
          <div class="comment_textarea">
            <?php print (render($q_a_item->comments['#form'])); ?>
          </div>
         <?php
         }
      }
      ?>
    </div>
  </div>
</div>
