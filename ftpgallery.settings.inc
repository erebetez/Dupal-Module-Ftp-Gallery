<?php

function ftpgallery_admin() {
  $form = array();

  $form['ftpgallery_allowedfiletypes'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed file types for the gallery'),
    '#default_value' => variable_get('ftpgallery_allowedfiletypes', 'jpg jpeg png'),
    '#description' => t("These file types are red and displayed in the gallery."),
    '#required' => TRUE,
  );

  $form['ftpgallery_thumbprefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail prefix'),
    '#default_value' => variable_get('ftpgallery_thumbprefix', 'thumb_'),
    '#description' => t("The prefix of the thumbnail files."),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

function ftpgallery_admin_validate($form, &$form_state) {
  $inputstring = $form_state['values']['ftpgallery_allowedfiletypes'];
  $inputstring = _ftpgallery_formatFileTypeString($inputstring);
  $form_state['values']['ftpgallery_allowedfiletypes'] = $inputstring;

  $form_state['values']['ftpgallery_thumbprefix'] = check_plain($form_state['values']['ftpgallery_thumbprefix']);
//     form_set_error('ftpgallery_allowedfiletypes', t('text'));
}

function _ftpgallery_formatFileTypeString($inputstring){
  $removeChars = array(".", ",", ";");
  $inputstring = str_replace($removeChars, " ", $inputstring);
  $inputstring = strtolower($inputstring);

  $inputArray = explode(" ", $inputstring);

  $inputArray = preg_grep("/^([a-z0-9]+)$/", $inputArray);

  return implode(" ", $inputArray);
}