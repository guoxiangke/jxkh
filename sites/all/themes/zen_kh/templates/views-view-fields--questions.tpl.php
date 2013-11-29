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
<?php //dpm($fields);
// Themer can change any div class name for theme question views page...-guo
?>

<div class="question clearfix">
	<div class="container-fluid">
		<?php //field_ask_anonymous
			$q_author = $fields['name']->content;
			if(isset($fields['field_ask_anonymous']) && $fields['field_ask_anonymous']->content == 1) {
				$q_author = '<a href="#">匿名提问</a>';
			}
		?>
		<div class="q-author pull-left"> <?php print $picture; ?>
			<div class="commit pull-left">
				<div class="timestamp"><span><?php print $q_author; ?></span></div>
				<!-- 		<div class="username"></div> --> 
			</div>
		</div>
		<div class="q-main">
			<div class="head_wrap">
				<div class="q-title"><?php print $title; ?></div>
				<span class="time"><?php print $published_at; ?></span></div>
			<div class="q-body span12"><?php print $body; ?></div>
			<div class="q-statics">
				<div class="q-statics-top">
					<div class="q-vote"><?php print $value; ?></div>
					<div class="q-answers <?php print $fields['field_computed_answers']->content!='0'?'active':''?>"><!--<b class="triangle_top"></b>--><span class="number"><?php print $fields['field_computed_answers']->content; ?></span><span>回答</span> </div>
				</div>
				<?php // <div class="q-views"><?php print $totalcount; ? ></div> ?>
			</div>
			<div class="q-taglink container-fluid">
				<div class="tags"> <span class="tags-label"><?php echo t('Tags');?>:</span> <?php print $field_tags; ?> </div>
				<div class="links"> <span class="edit">
					<?php //print $edit_node; ?>
					</span> <span class="delete">
					<?php //print $delete_node; ?>
					</span> </div>
			</div>
		</div>
	</div>
</div>
