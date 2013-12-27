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

<div class="sbq_tags">
  <?php if(isset($field_tags)) print $field_tags; ?>
</div>
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
        <li class="sbq_date"><?php print $created; ?></li>
        <li><a href="#" class="sbq_add_reply_btn">
          <?php if ($node->comment_count == 0) {?>
            添加评论
          <?php } else {?>
            <?php print $node->comment_count; ?>条回复
          <?php }?>
        </a></li>
        <?php if(!empty($edit_node)): ?>
        <li class="edit"><?php print $edit_node; ?></li>
        <?php endif;?>
        <?php if(!empty($delete_node)): ?>
        <li class="delete"><?php print $delete_node; ?></li>
        <?php endif;?>
      </ul>
    </div>
    <div class="sbq_reply_wrap">
      <div class="sbq_reply_list">
        <ul>
          <li>
            <div class="sbq_user_pic"><a href="#" title="用户名"><img src="images/user_face2.jpg" width="24" height="24"  alt=""/></a></div>
            <div class="sbq_reply_list_content">
              <div class="sbq_user_name"><a href="#">伊丽莎白酱</a></div>
              <div class="sbq_text">快要好了的时候又发烧了38.5去医院灌肠第二天早上37.5晚上的时候又38.5去医院查血白细胞较少又做了一次灌肠.请问这种情况严重吗</div>
              <div class="sbq_date">2013/12/09</div>
            </div>
          </li>
        </ul>
      </div>
      <div class="comment_textarea" style="overflow-x: hidden; overflow-y: hidden; display: block;"> <a href="#" class="close"> <i class="icon-remove-sign"></i> </a>
        <form class="comment-form" action="/comment/reply/21619" method="post" id="comment-form--6" accept-charset="UTF-8">
          <div>
            <div class="field-type-text-long field-name-comment-body field-widget-text-textarea form-wrapper" id="edit-comment-body--6">
              <div id="comment-body-add-more-wrapper--6">
                <div class="form-item form-type-textarea form-item-comment-body-und-0-value">
                  <label for="edit-comment-body-und-0-value--6"> 评论 <span class="form-required" title="此项必填。">*</span> </label>
                  <div class="form-textarea-wrapper resizable textarea-processed resizable-textarea">
                    <textarea class="text-full form-textarea required" id="edit-comment-body-und-0-value--6" name="comment_body[und][0][value]" cols="60" rows="1"></textarea>
                    <div class="grippie"></div>
                  </div>
                </div>
              </div>
            </div>
            <input type="hidden" name="form_build_id" value="form-4Z16ZfA4C_5qhh-NcxgEzPqoAtDr_DiBaqz4SNODsnc">
            <input type="hidden" name="form_token" value="oK2bU1oaVC9CrLVlyo9wAMFDLxbNJBbThaYqM5TaT7k">
            <input type="hidden" name="form_id" value="comment_node_question_form">
            <div class="form-actions form-wrapper" id="edit-actions--6">
              <input type="submit" id="edit-submit--6" name="op" value="评论" class="form-submit ajax-processed">
            </div>
          </div>
        </form>
      </div>
    </div>
  </div>
</div>
