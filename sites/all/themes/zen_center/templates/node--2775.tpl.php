<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>
<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
    <header>
      <?php print render($title_prefix); ?>
      <?php if (!$page && $title): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
        <p class="submitted">
          <?php print $user_picture; ?>
          <?php print $submitted; ?>
        </p>
      <?php endif; ?>

      <?php if ($unpublished): ?>
        <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
      <?php endif; ?>
    </header>
  <?php endif; ?>

  <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    print render($content);
  ?>
<!---->
<div id="node_wiki_child_full_group_content" class="group-content field-group-div">
  <div class="sbq-group-content-tab">
    <div class="field-label active">规格参数</div>
    <div class="field-label">科学测评</div>
  </div>
  <div class="wiki-field field field-name-body field-type-text-with-summary field-label-above">
    <div class="field-items">
      <div class="field-item even" property="content:encoded">
        <p>其实title 应该为：三诺安稳血糖仪血糖？？ 细胞指向：血糖仪～</p>
        <p>参数：</p>
        <table border="1" cellpadding="0" cellspacing="0">
          <tbody>
            <tr>
              <td>
                <p>测量时间</p>
              </td>
              <td>
                <p>5秒（机内）/10秒（机外）</p>
              </td>
            </tr>
            <tr>
              <td>
                <p>测量方法</p>
              </td>
              <td>
                <p>光化学法</p>
              </td>
            </tr>
            <tr>
              <td>
                <p>测量范围</p>
              </td>
              <td>
                <p>0.6-33.3mmol/L</p>
              </td>
            </tr>
            <tr>
              <td>
                <p>系统运行条件</p>
              </td>
              <td>
                <p>10-40℃</p>
              </td>
            </tr>
            <tr>
              <td>
                <p>显示屏</p>
              </td>
              <td>
                <p>LCD</p>
              </td>
            </tr>
            <tr>
              <td>
                <p>内存容量</p>
              </td>
              <td>
                <p>350</p>
              </td>
            </tr>
            <tr>
              <td>
                <p>自动关闭</p>
              </td>
              <td>
                <p>支持</p>
              </td>
            </tr>
          </tbody>
        </table>
        <p>优点 缺点</p>
        <table border="1" cellpadding="0" cellspacing="0">
          <tbody>
            <tr>
              <td>
                <p>系统运行条件系统运行条件</p>
                <p>系统运行条件系统运行条件</p>
                <p>&nbsp;</p>
              </td>
              <td>
                <p>10-40℃运行条件系统运行条件运行条件系统运行条件运行条件系统运行条件运行条件系统运行条件</p>
              </td>
            </tr>
          </tbody>
        </table>
        <p>&nbsp;</p>
        <p>&nbsp;</p>
        <p>&nbsp;</p>
      </div>
    </div>
  </div>
  <div class="wiki-field sbq-field_video_warpper">
  <!--Video List-->
  <div class="sbq-field-video-list">
  <div class="field field-name-field-wiki-video field-type-media field-label-above">
    <div class="field-items">
      <div class="field-item even">
        <div class="media-youku-outer-wrapper" id="media-youku-1" style="width: 640px; height: 480px;">
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
</div>
<!---->
  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
