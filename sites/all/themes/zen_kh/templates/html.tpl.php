<?php
/**
 * @file
 * Returns the HTML for the basic html structure of a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728208
 */
?><!DOCTYPE html>
<!--[if IEMobile 7]><html class="iem7" <?php print $html_attributes; ?>><![endif]-->
<!--[if lte IE 6]><html class="lt-ie9 lt-ie8 lt-ie7" <?php print $html_attributes; ?>><![endif]-->
<!--[if (IE 7)&(!IEMobile)]><html class="lt-ie9 lt-ie8" <?php print $html_attributes; ?>><![endif]-->
<!--[if IE 8]><html class="lt-ie9" <?php print $html_attributes; ?>><![endif]-->
<!--[if (gte IE 9)|(gt IEMobile 7)]><!--><html <?php print $html_attributes . $rdf_namespaces; ?>><!--<![endif]-->

  <head>
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>

    <?php if ($default_mobile_metatags): ?>
      <meta name="MobileOptimized" content="width">
      <meta name="HandheldFriendly" content="true">
      <meta name="viewport" content="width=device-width">
    <?php endif; ?>
    <meta http-equiv="cleartype" content="on">

    <?php print $styles; ?>
    <?php print $scripts; ?>
    <?php if ($add_html5_shim and !$add_respond_js): ?>
      <!--[if lt IE 9]>
      <script src="<?php print $base_path . $path_to_zen; ?>/js/html5.js"></script>
      <![endif]-->
    <?php elseif ($add_html5_shim and $add_respond_js): ?>
      <!--[if lt IE 9]>
      <script src="<?php print $base_path . $path_to_zen; ?>/js/html5-respond.js"></script>
      <![endif]-->
    <?php elseif ($add_respond_js): ?>
      <!--[if lt IE 9]>
      <script src="<?php print $base_path . $path_to_zen; ?>/js/respond.js"></script>
      <![endif]-->
    <?php endif; ?>
  </head>
  <body class="<?php print $classes; ?>" <?php print $attributes; ?>>
    <?php if ($skip_link_text && $skip_link_anchor): ?>
      <p id="skip-link">
        <a href="#<?php print $skip_link_anchor; ?>" class="element-invisible element-focusable"><?php print $skip_link_text; ?></a>
      </p>
    <?php endif; ?>
    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $page_bottom; ?>
    <?php if (!$user->uid) { ?>
      <!-- Modal sbq_customer_register_form_modal -->
      <div class="modal fade" id="sbq_customer_register_form_modal" tabindex="-1" role="dialog" aria-labelledby="sbq_customer_register_form_modal_label" aria-hidden="true">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
              <h4 class="modal-title" id="sbq_customer_register_form_modal_label">普通注册</h4>
            </div>
            <div class="modal-body">
              <?php print $customer_register_form; ?>
            </div>
          </div><!-- /.modal-content -->
        </div><!-- /.modal-dialog -->
      </div><!-- /.modal -->
      <!-- Modal sbq_doctor_register_form_modal -->
      <div class="modal fade" id="sbq_doctor_register_form_modal" tabindex="-1" role="dialog" aria-labelledby="sbq_doctor_register_form_modal_label" aria-hidden="true">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
              <h4 class="modal-title" id="sbq_doctor_register_form_modal_label">医生注册</h4>
            </div>
            <div class="modal-body">
              <?php print $doctor_register_form; ?>
            </div>
          </div><!-- /.modal-content -->
        </div><!-- /.modal-dialog -->
      </div><!-- /.modal -->
      <!-- Modal sbq_user_login_form_modal -->
      <div class="modal fade" id="sbq_user_login_form_modal" tabindex="-1" role="dialog" aria-labelledby="sbq_user_login_form_modal_label" aria-hidden="true">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
              <h4 class="modal-title" id="sbq_user_login_form_modal_label">用户登录</h4>
            </div>
            <div class="modal-body">
              <?php print $user_login_form; ?>
            </div>
          </div><!-- /.modal-content -->
        </div><!-- /.modal-dialog -->
      </div><!-- /.modal -->
      <!-- Modal sbq_doctor_quick_login -->
      <div class="modal fade" id="sbq_doctor_quick_login_modal" tabindex="-1" role="dialog" aria-labelledby="sbq_user_login_form_modal_label" aria-hidden="true">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
              <h4 class="modal-title" id="sbq_user_login_form_modal_label">医生快速通道</h4>
            </div>
            <div class="modal-body">
              <div class="quick-user-login">
                <?php print $user_login_block; ?>
              </div>
              <div class="quick-doctor-login">
                 <?php print $doctor_quick_login_form; ?>
              </div>
            </div>
          </div><!-- /.modal-content -->
        </div><!-- /.modal-dialog -->
      </div><!-- /.modal -->
    <?php } ?>
  </body>
</html>
