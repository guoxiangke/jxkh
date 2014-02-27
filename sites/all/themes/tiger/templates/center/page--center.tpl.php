<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
define('SBQ_CENTER_EDU_VIDEO_TID', 24706);
define('SBQ_CENTER_EDU_ARTICLE_TID', 24705);
  $theme_path = drupal_get_path('theme', 'tiger');

?>

<?php
  global $user;
  $menu_index_active = '';
  $menu_reservation_active = '';
  $menu_info_active = '';
  $menu_edu_active = '';
  $menu_messages_active = '';
  $menu_manage_active = '';

  $left_reservation_active = '';
  $left_reservation_manage_active = '';
  $left_reservation_my_active = '';

  $left_edu_active = '';
  $left_edu_article_active = '';

  $left_questions_active = '';

  $left_reservation_manage_active = '';
  $left_reservation_settings_active = '';
  $left_center_edit_active = '';
  $left_edu_add_active = '';
  $left_notice_add_active = '';

  $is_edu = FALSE;
  $is_info = FALSE;
  $is_reservation = FALSE;
  $is_edu = FALSE;
  $is_manage = FALSE;
  if (in_array('index', arg())) {
    $menu_index_active = ' class="active"';
  } elseif (in_array('add', arg()) || in_array('edit', arg()) || in_array('manage', arg()) || in_array('settings', arg()) ){
    $menu_manage_active = ' class="active"';
    $is_manage = TRUE;
    if (in_array('manage', arg())) {
      $left_reservation_manage_active = ' class="active"';
    } elseif (in_array('settings', arg())) {
      $left_reservation_settings_active = ' class="active"';
    } elseif (in_array('edit', arg())) {
      $left_center_edit_active = ' class="active"';
    } elseif (in_array('add', arg()) && in_array('sbq-center-edu', arg())) {
      $left_edu_add_active = ' class="active"';
    } elseif (in_array('add', arg()) && in_array('center-notice', arg())) {
      $left_notice_add_active = ' class="active"';
    }

  }elseif (in_array('reservation', arg())) {
    $menu_reservation_active = ' class="active"';
    $is_reservation = TRUE;
    if (in_array('manage', arg())) {
      $left_reservation_manage_active = ' class="active"';
    } elseif (in_array('my', arg())) {
      $left_reservation_my_active = ' class="active"';
    } else {
      $left_reservation_active = ' class="active"';
    }
  } elseif (in_array('info', arg())) {
    $menu_info_active = ' class="active"';
    $is_info = TRUE;
  } elseif (in_array('messages', arg())) {
    $menu_messages_active = ' class="active"';
  } elseif (in_array('edu', arg())) {
    $menu_edu_active = ' class="active"';
    $is_edu = TRUE;
    if (in_array('article', arg())) {
      $left_edu_article_active = ' class="active"';
    } else {
      $left_edu_active = ' class="active"';
    }
  } elseif (isset($node) && $node->type == 'sbq_center_edu') {
    $menu_edu_active = ' class="active"';
    $is_edu = TRUE;
    if ($node->field_sbq_center_edu_tax['und'][0]['tid'] == SBQ_CENTER_EDU_VIDEO_TID) {
      $left_edu_active = ' class="active"';
    }
    if ($node->field_sbq_center_edu_tax['und'][0]['tid'] == SBQ_CENTER_EDU_ARTICLE_TID) {
      $left_edu_article_active = ' class="active"';
    }
  }
  if (in_array('questions', arg()) || in_array('question', arg())) {
    $left_questions_active = ' class="active"';
  }

  $center = node_load($center_id);
  $is_center_owner = FALSE;
  if ($user->uid == $center->uid) {
    $is_center_owner = TRUE;
  }
  $edu_menu_text = '健康教育';
  if (isset($center->field_sbq_center_edu_switch['und'][0]['value'])) {
    $text = $center->field_sbq_center_edu_switch['und'][0]['value'];
    if (strlen(trim($text)) > 0) {
      $edu_menu_text = $text;
    }
  }
  $pm_thread_id = _sbq_get_pm_thread_id_to_sbqcenter($center->uid);
  $header_image = file_create_url($center->field_image['und'][0]['uri']);
?>
<div class="header">
  <div class="header_inner" style="background:url(<?php print $header_image; ?>) no-repeat;">
    <div class="sbq_header_login">
      <?php if (!$logged_in): ?>
      <div class="sbq_user_links">
        <a href="/user/login" class="log">登录</a>|<a href="/customer/register">注册</a>
      </div>
      <div class="sbq_user_pic">
        <a href="/user/login"><img src="/<?php print $theme_path; ?>/image/default_avatar.png" width="50" height="50"  alt=""/></a>
      </div>
      <?php endif; ?>
      <?php if ($logged_in): ?>
      <?php
        $name = theme('username', array('account' => $user));
        $picture = theme('user_picture', array('account' =>$user));
      ?>
      <div class="sbq_user_links">
        欢迎您，<?php print $name; ?>|<a href="/user/logout">退出</a>
      </div>
      <div class="sbq_user_pic">
        <?php print $picture; ?>
      </div>
      <?php endif; ?>
    </div>
  <a href="#" id="sbq_gototop" style="display: none;"></a></div>
</div>
<div class="sbq_hospital_nav">
  <ul>
    <li<?php print $menu_index_active; ?>><?php print l('医院首页', 'center/'.$center_id.'/index'); ?></li>
    <li<?php print $menu_reservation_active; ?>><?php print l('预约就诊', 'center/'.$center_id.'/reservation'); ?></li>
    <?php if ($logged_in): ?>
      <?php if ($is_center_owner): ?>
        <li<?php print $menu_messages_active; ?>><?php print l('咨询管理', 'messages'); ?></li>
      <?php else: ?>
        <?php if ($pm_thread_id): ?>
          <li<?php print $menu_messages_active; ?>><?php print l('咨询医生', 'messages/view/'.$pm_thread_id); ?></li>
        <?php else: ?>
          <li<?php print $menu_messages_active; ?>><?php print l('咨询医生', 'messages/new/'.$owner_uid); ?></li>
        <?php endif; ?>
      <?php endif; ?>
    <?php else: ?>
      <li<?php print $menu_messages_active; ?>><?php print l('咨询医生', 'user/login', array('query' => array('destination' => 'center/'.$center_id.'/index'))); ?></li>
    <?php endif; ?>
    <li<?php print $menu_edu_active; ?>><?php print l($edu_menu_text, 'center/'.$center_id.'/edu'); ?></li>
    <li<?php print $menu_info_active; ?>><?php print l('中心介绍', 'center/'.$center_id.'/info'); ?></li>
    <?php if ($is_center_owner): ?>
      <li<?php print $menu_manage_active; ?>><?php print l('中心管理', 'center/'.$center_id.'/reservation/manage'); ?></li>
    <?php endif; ?>
  </ul>
</div>
<div class="body">
  <div class="main">
    <?php if ($messages): ?>
    <div class="sbq_messages">
      <?php print $messages; ?>
    </div>
    <?php endif; ?>
    <div class="sidebar_first sidebar sbq_hospital_sidebar">
      <?php print render($page['sidebar_first']); ?>
      <?php if (!$is_info): ?>
      <div class="sbq_hospital_sub_nav">
        <?php if ($is_edu): ?>
        <ul>
          <li<?php print $left_edu_article_active; ?>><?php print l('专科资讯', 'center/'.$center_id.'/edu/article'); ?></li>
          <li<?php print $left_edu_active; ?>><?php print l('精选视频', 'center/'.$center_id.'/edu'); ?></li>
        </ul>
        <?php elseif ($is_reservation): ?>
        <ul>
          <li<?php print $left_reservation_active; ?>><?php print l('预约就诊', 'center/'.$center_id.'/reservation'); ?></li>
          <?php if($is_admin || $is_center_owner): ?>
          <li<?php print $left_reservation_manage_active; ?>><?php print l('预约管理', 'center/'.$center_id.'/reservation/manage'); ?></li>
          <?php elseif($logged_in): ?>
          <li<?php print $left_reservation_my_active; ?>><?php print l('我的预约', 'center/'.$center_id.'/reservation/my'); ?></li>
          <?php endif; ?>
          <li><?php print l('就诊流程', 'node/'.$visit_nid); ?></li>
          <li><?php print l('治疗方案', 'node/'.$plan_nid); ?></li>
        </ul>
        <?php elseif ($is_manage): ?>
        <ul>
          <?php if($is_admin || $is_center_owner): ?>
          <li<?php print $left_center_edit_active; ?>><?php print l('中心管理', 'node/'.$center_id.'/edit'); ?></li>
          <li<?php print $left_reservation_manage_active; ?>><?php print l('预约管理', 'center/'.$center_id.'/reservation/manage'); ?></li>
          <li<?php print $left_reservation_settings_active; ?>><?php print l('预约设置', 'center/'.$center_id.'/reservation/settings'); ?></li>
          <li<?php print $left_edu_add_active; ?>><?php print l('添加健康教育', 'node/add/sbq-center-edu', array('query' => array('og_group_ref' => $center_id))); ?></li>
          <li<?php print $left_notice_add_active; ?>><?php print l('添加文章', 'node/add/center-notice', array('query' => array('og_group_ref' => $center_id))); ?></li>
          <?php endif; ?>
        </ul>
        <?php else: ?>
        <ul>
          <li<?php print $left_reservation_active; ?>><?php print l('预约就诊', 'center/'.$center_id.'/reservation'); ?></li>
          <li<?php print $left_questions_active; ?>><?php print l('常见问题解答', 'center/'.$center_id.'/questions'); ?></li>
          <?php if ($expert_nid): ?>
          <li><?php print l('专家团队', 'center/'.$center_id.'/info', array('fragment' => 'node-'.$expert_nid)); ?></li>
          <?php elseif($is_admin || $is_center_owner): ?>
          <li><?php print l('专家团队', 'node/add/center-notice', array('query' => array('og_group_ref' => $center_id))); ?></li>
          <?php endif; ?>

        </ul>
        <?php endif; ?>
      </div>
      <?php endif; ?>
    </div> <!-- /.sidebar-first -->

    <div class="content">
      <?php print render($page['content']); ?>
    </div>

    <?php if (isset($page['sidebar_second'])&& $page['sidebar_second']): ?>
      <div class="sidebar_second sidebar">
        <?php print render($page['sidebar_second']); ?>
      </div> <!-- /.sidebar-second -->
    <?php endif; ?>
  </div>
</div>
<div class="footer">
  <div class="footer_inner">
    <div class="sbq_about_link">
      <?php
      // <ul>
      //   <li><a href="/contact.html">联系我们</a></li>
      //   <li><a href="/services.html">注册服务条款</a></li>
      //   <li><a href="/copyright.html">免责声明</a></li>
      //   <li><a href="/join.html">加入我们</a></li>
      //   <li><a href="/about.html">关于我们</a></li>
      // </ul>
      ?>
    </div>
    <?php //<div class="sbq_copy">© 2014 伤不起 中国最真实的医疗评价平台(<a href="http://www.miitbeian.gov.cn" target="_bank"> 京ICP备13032461号-1</a>) </div> ?>
  </div>
  <?php print render($page['footer']); ?>
</div> <!-- /#footer -->
