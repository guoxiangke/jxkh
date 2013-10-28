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
/*foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
  <?php print $field->wrapper_suffix; ?>
<?php endforeach; */
?>
<?php
// dpm($fields);
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
      // $q_author = $name;
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

<div class="question clearfix">
  <?php if($node->type == 'question'):?>
  <div class="title"><?php print $title; ?></div>
  <?php endif?>
  <div class="q-body clearfix">
    <div class="votes pull-left"><?php print $value_1; ?></div>
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
            <div class="author-item q-author pull-left">
              <?php print $picture; ?>
              <div class="commit pull-left">
                <div class="timestamp"><span class="edit"><?php print $name; //Edited by ?></span><span><?php print format_date($node->revision_timestamp, 'sbq_date_medium_revert'); ?></span></div>
              </div>
            </div>
            <?php
          }else{
            //show who edit ,who create.
            $editor = user_load($node->revision_uid);
             ?>
            <div class="author-item q-author pull-left">
              <?php print $picture; ?>
              <div class="commit pull-left">
<!--                 <div class="timestamp"><span class="create">Create</span>< ?php //print $created; ?></div>
                <div class="username">< ?php //print $name; ?></div> -->

               <div class="timestamp"><span class="create"><?php print $name; //Created by ?></span><span><?php print $created; ?></span></div>

              </div>
            </div>
            <?php
          }
          ?>

        </div>

          <div class="links">
        <?php if(0&&user_access('Authorized to share a node')) : ?>
        <span class="share"><a class="btn btn-mini use-ajax" href="<?php print $share_a_node; ?>"><?php print t('Share this question') ?></a></span>
        <?php endif;?>
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
foreach ( $view->result as $q_a_item) {//both for question & answers.
 if(isset($q_a_item->comments) && isset($q_a_item->comments['#form']['nid']) && $row->nid==$q_a_item->comments['#form']['nid']['#value']){
   ?>
   <div class="comments_<?php echo $q_a_item->_field_data['nid']['entity']->type;//question/answer?>">
     <?php print render($q_a_item->comments['#content']);?>
     <div class="clearfix">
      <div class="q-feedback">
        <a class="comment_button btn btn-mini" data-trigger="click" data-placement='bottom'><i class="icon-comment icon-small"></i><?php echo t('comments');?></a>
      </div>

       <!--  <div class="q-feedback">
        <a class="fed_button btn btn-mini btn-link" data-trigger="click" data-content="<?php //print htmlentities($value_1); ?>"><i class="icon-pencil icon-small"></i>Feedback</a>
        </div> 
 -->
       <!-- <a class="fed_button btn btn-mini btn-link"   data-content="<?php //print htmlentities($value_1); ?>"><i class="icon-pencil icon-small"></i>sdf</a> -->


<!--         <div class="feedback-wrapper">
           <?//php print($value_1)?>
        </div> -->

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

