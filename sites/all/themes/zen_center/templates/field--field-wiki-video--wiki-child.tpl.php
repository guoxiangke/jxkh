<?php

/**
 * @file field.tpl.php
 * Default template implementation to display the value of a field.
 *
 * This file is not used and is here as a starting point for customization only.
 * @see theme_field()
 *
 * Available variables:
 * - $items: An array of field values. Use render() to output them.
 * - $label: The item label.
 * - $label_hidden: Whether the label display is set to 'hidden'.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - field: The current template type, i.e., "theming hook".
 *   - field-name-[field_name]: The current field name. For example, if the
 *     field name is "field_description" it would result in
 *     "field-name-field-description".
 *   - field-type-[field_type]: The current field type. For example, if the
 *     field type is "text" it would result in "field-type-text".
 *   - field-label-[label_display]: The current label position. For example, if
 *     the label position is "above" it would result in "field-label-above".
 *
 * Other variables:
 * - $element['#object']: The entity to which the field is attached.
 * - $element['#view_mode']: View mode, e.g. 'full', 'teaser'...
 * - $element['#field_name']: The field name.
 * - $element['#field_type']: The field type.
 * - $element['#field_language']: The field language.
 * - $element['#field_translatable']: Whether the field is translatable or not.
 * - $element['#label_display']: Position of label display, inline, above, or
 *   hidden.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 *
 * @ingroup themeable


<!--
THIS FILE IS NOT USED AND IS HERE AS A STARTING POINT FOR CUSTOMIZATION ONLY.
See http://api.drupal.org/api/function/theme_field/7 for details.
After copying this file to your theme's folder and customizing it, remove this
HTML comment.
-->

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>
    <?php foreach ($items as $delta => $item): ?>
      <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>><?php print render($item); ?></div>
    <?php endforeach; ?>
  </div>
</div>
<!--     -->
 */
?>
<div class="sbq-field_video_warpper">
  <!--Video List-->
  <div class="sbq-field-video-list">
  <div class="field field-name-field-wiki-video field-type-media field-label-above"><div class="field-label">科学测评:&nbsp;</div><div class="field-items"><div class="field-item even"><div class="media-youku-outer-wrapper" id="media-youku-1" style="width: 640px; height: 480px;">
  <div class="media-youku-preview-wrapper" id="media_youku_XNTg4MTg3MDA4_1">
        <object width="640" height="480">
      <param name="movie" value="http://www.youku.com/v/XNTg4MTg3MDA4">
      <param name="allowFullScreen" value="true">
      <param name="wmode" value="transparent">
      <embed src="http://player.youku.com/player.php/sid/XNTg4MTg3MDA4/.v.swf" type="application/x-shockwave-flash" width="640" height="480" allowfullscreen="true">
    </object>    <script type="text/javascript">
      if (Drupal.settings && Drupal.media_youku) {
        Drupal.settings.media_youku = Drupal.settings.media_youku || {};
        Drupal.settings.media_youku["media_youku_XNTg4MTg3MDA4_1"] = {};
        Drupal.settings.media_youku["media_youku_XNTg4MTg3MDA4_1"].width = 640;
        Drupal.settings.media_youku["media_youku_XNTg4MTg3MDA4_1"].height = 480;
        Drupal.settings.media_youku["media_youku_XNTg4MTg3MDA4_1"].video_id = "XNTg4MTg3MDA4";
        Drupal.settings.media_youku["media_youku_XNTg4MTg3MDA4_1"].fullscreen = true;
        Drupal.settings.media_youku["media_youku_XNTg4MTg3MDA4_1"].id = "media_youku_XNTg4MTg3MDA4_1_iframe";
        Drupal.settings.media_youku["media_youku_XNTg4MTg3MDA4_1"].options = { autoplay: 0 };
        Drupal.media_youku.insertEmbed("media_youku_XNTg4MTg3MDA4_1");
      }
    </script>  </div>
</div>
</div><div class="field-item odd"><div class="media-youku-outer-wrapper" id="media-youku-2" style="width: 640px; height: 480px;">
  <div class="media-youku-preview-wrapper" id="media_youku_XNTY3NzU5OTAw_2">
        <object width="640" height="480">
      <param name="movie" value="http://www.youku.com/v/XNTY3NzU5OTAw">
      <param name="allowFullScreen" value="true">
      <param name="wmode" value="transparent">
      <embed src="http://player.youku.com/player.php/sid/XNTY3NzU5OTAw/.v.swf" type="application/x-shockwave-flash" width="640" height="480" allowfullscreen="true">
    </object>    <script type="text/javascript">
      if (Drupal.settings && Drupal.media_youku) {
        Drupal.settings.media_youku = Drupal.settings.media_youku || {};
        Drupal.settings.media_youku["media_youku_XNTY3NzU5OTAw_2"] = {};
        Drupal.settings.media_youku["media_youku_XNTY3NzU5OTAw_2"].width = 640;
        Drupal.settings.media_youku["media_youku_XNTY3NzU5OTAw_2"].height = 480;
        Drupal.settings.media_youku["media_youku_XNTY3NzU5OTAw_2"].video_id = "XNTY3NzU5OTAw";
        Drupal.settings.media_youku["media_youku_XNTY3NzU5OTAw_2"].fullscreen = true;
        Drupal.settings.media_youku["media_youku_XNTY3NzU5OTAw_2"].id = "media_youku_XNTY3NzU5OTAw_2_iframe";
        Drupal.settings.media_youku["media_youku_XNTY3NzU5OTAw_2"].options = { autoplay: 0 };
        Drupal.media_youku.insertEmbed("media_youku_XNTY3NzU5OTAw_2");
      }
    </script>  </div>
</div>
</div><div class="field-item even"><div class="media-youku-outer-wrapper" id="media-youku-3" style="width: 640px; height: 480px;">
  <div class="media-youku-preview-wrapper" id="media_youku_XNTM5NjQ3ODgw_3">
        <object width="640" height="480">
      <param name="movie" value="http://www.youku.com/v/XNTM5NjQ3ODgw">
      <param name="allowFullScreen" value="true">
      <param name="wmode" value="transparent">
      <embed src="http://player.youku.com/player.php/sid/XNTM5NjQ3ODgw/.v.swf" type="application/x-shockwave-flash" width="640" height="480" allowfullscreen="true">
    </object>    <script type="text/javascript">
      if (Drupal.settings && Drupal.media_youku) {
        Drupal.settings.media_youku = Drupal.settings.media_youku || {};
        Drupal.settings.media_youku["media_youku_XNTM5NjQ3ODgw_3"] = {};
        Drupal.settings.media_youku["media_youku_XNTM5NjQ3ODgw_3"].width = 640;
        Drupal.settings.media_youku["media_youku_XNTM5NjQ3ODgw_3"].height = 480;
        Drupal.settings.media_youku["media_youku_XNTM5NjQ3ODgw_3"].video_id = "XNTM5NjQ3ODgw";
        Drupal.settings.media_youku["media_youku_XNTM5NjQ3ODgw_3"].fullscreen = true;
        Drupal.settings.media_youku["media_youku_XNTM5NjQ3ODgw_3"].id = "media_youku_XNTM5NjQ3ODgw_3_iframe";
        Drupal.settings.media_youku["media_youku_XNTM5NjQ3ODgw_3"].options = { autoplay: 0 };
        Drupal.media_youku.insertEmbed("media_youku_XNTM5NjQ3ODgw_3");
      }
    </script>  </div>
</div>
</div></div></div>
  </div>
  <!--End of Video List-->
  <!--Video Title List-->
  <div class="sbq_field_title_list">
  <div class="field field-name-field-wiki-video field-type-media field-label-above">
    <div class="sbq-wiki-video-field-label">专家测评:&nbsp;</div>
    <div class="field-items">
      <div class="field-item even">
        <span class="file">
          <img class="file-icon" alt="" title="video/youku" src="/modules/file/icons/video-x-generic.png">
          <a href="http://v.youku.com/v_show/id_XNTg4MTg3MDA4.html" type="video/youku; length=0">三诺安稳血糖仪操作视频（超清）</a>
        </span>
      </div>
      <div class="field-item odd"><span class="file"><img class="file-icon" alt="" title="video/youku" src="/modules/file/icons/video-x-generic.png"> <a href="http://v.youku.com/v_show/id_XNTY3NzU5OTAw.html" type="video/youku; length=0">罗氏血糖仪</a></span></div><div class="field-item even"><span class="file"><img class="file-icon" alt="" title="video/youku" src="/modules/file/icons/video-x-generic.png"> <a href="http://v.youku.com/v_show/id_XNTM5NjQ3ODgw.html" type="video/youku; length=0">鱼跃血糖仪操作视频</a></span></div></div></div>
    <div class="more-link">
      <a href="#">
        more  </a>
    </div>
    </div>
  <!--End of Video Title List-->
</div>