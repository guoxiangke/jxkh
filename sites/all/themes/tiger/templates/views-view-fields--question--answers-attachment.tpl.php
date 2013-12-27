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
<?php /*foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
  <?php print $field->wrapper_suffix; ?>
<?php endforeach; */?>
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
  $author = user_load($node->uid);
  kpr($node);
  kpr($author);
  global $base_url, $user;
  $share_a_node = $base_url.'/node/'.$row->nid.'/share/'.$user->uid.'/nojs';
?>

<div class="sbq_answer">
  <div class="votes">
    <a href="#" class="up">
      <span class="arrow"></span>
      <span class="count">0</span>
    </a>
    <a href="#" class="down">
      <span class="arrow"></span>
    </a>
  </div>
  <div class="sbq_content">
    <div class="sbq_user_name"><?php print $name;?></div>
    <div class="sbq_user_pic"><?php print $picture; ?></div>
    <div class="sbq_text"><?php print $body; ?></div>
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


<!---------------------------------------------------------------------------->
<div class="question clearfix">
  <?php if($node->type == 'question'):?>
  <div class="title"><?php print $title; ?></div>
  <?php endif?>
  <div class="q-body clearfix">
    <div class="votes pull-left"><?php print $value; ?></div>
      <div class="q-margin">
    <div class="q-content span12">
      <div class="q-body"><p><?php print $body; ?></p></div>
      <?php if(!empty($field_attachments)):?>
      <div class="q-files"><?php print $field_attachments; ?></div>
      <?php endif;?>
      <div class="tags"><span class="tags-label"><?php echo t('Tags');?>:</span>
      <?php if(isset($field_tags)) print $field_tags; ?>
      </div>

      <div class="q-info clearfix">
        <div class="q-author-block pull-right">
          <?php
          if($node->created == $node->changed){
            //not be changed,only show who create it.
            ?>
            <div class="author-item q-author pull-left">
              <?php print $picture; ?>
              <div class="commit pull-left">
                <div class="timestamp"><span class="create"><?php print $name; //Created by ?></span><span><?php print $created; ?></span></div>
              </div>
            </div>
            <?php
          }elseif($node->revision_uid == $node->uid){
            //only show the author had edit it.
            ?>
            <?php
          }else{
            //show who edit ,who create.
            $editor = user_load($node->revision_uid);
             ?>
            <div class="author-item q-author q-edit pull-left">
              <?php
              $variables = array(
                'style_name' => 'profile_small',
                'path' =>$editor->picture->uri,

              );
              print theme_image_style($variables); ?>
              <div class="commit pull-left">
                <div class="timestamp"><span class="edit">Edited by <?php print l(format_username($editor),'user/'.$editor->uid); ?></span><span><?php print format_date($node->revision_timestamp, 'sbq_date_medium_revert'); ?> </span></div>
              </div>
            </div>
            <div class="author-item q-author pull-left">
              <?php print $picture; ?>
              <div class="commit pull-left">
<!--                 <div class="timestamp"><span class="create">Create</span><?php print $created; ?></div>
                <div class="username"><?php print $name; ?></div> -->

               <div class="timestamp"><span class="create"><?php print $name; //Created by ?></span><span><?php print $created; ?></span></div>

              </div>
            </div>
            <?php
          }
          ?>

        </div>

          <div class="links">
        <?php if(isset($accept_link)): ?>
        <span class="accept"><?php print $accept_link; ?></span>
        <?php endif;?>
        <?php if(!empty($edit_node)): ?>
        <span class="edit"><?php print $edit_node; ?></span>
        <?php endif;?>
        <?php if(!empty($delete_node)): ?>
        <span class="delete"><?php print $delete_node; ?></span>
        <?php endif;?>
      </div>
      </div>
      <?php
      if(user_is_logged_in())
foreach ( $view->result as $q_a_item) {//both for question & answers.
 if(isset($q_a_item->comments) && $row->nid==$q_a_item->comments['#form']['nid']['#value']){
   ?>
   <div class="comments_<?php echo $q_a_item->_field_data['nid']['entity']->type;//question/answer?>">
     <?php print render($q_a_item->comments['#content']);?>
     <div class="clearfix">
      <div class="q-feedback">
        <a class="comment_button btn btn-mini" data-trigger="click" data-placement='bottom'><i class="icon-comment icon-small"></i><?php echo t('comments');?></a>
      </div>
     </div>
    <div class="comment_textarea">
      <a href="#" class="close"><i class="icon-remove-sign"></i></a>
      <?php print (render($q_a_item->comments['#form'])); ?>
    </div>
   </div>
   <?php
   }
}
?>
    </div>
    </div>
  </div>
</div>

