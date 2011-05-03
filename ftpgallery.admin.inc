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

//   $form['ftpgallery_thumbprefix'] = array(
//     '#type' => 'textfield',
//     '#title' => t('Thumbnail prefix or subfolder'),
//     '#default_value' => variable_get('ftpgallery_thumbprefix', 'thumb_'),
//     '#description' => t("The prefix of the thumbnail files or the subfolder with the thumbnails inside."),
//     '#required' => TRUE,
//   );

  $form['ftpgallery_gallerybasedir'] = array(
    '#type' => 'textfield',
    '#title' => t('Base dir for all FTP gallerys'),
    '#default_value' => variable_get('ftpgallery_gallerybasedir', 'files'),
    '#description' => t("The base dir relativ to the drupal installation with all the gallerys"),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

function ftpgallery_admin_validate($form, &$form_state) {
  $inputstring = $form_state['values']['ftpgallery_allowedfiletypes'];
  $inputstring = _ftpgallery_formatFileTypeString($inputstring);
  $form_state['values']['ftpgallery_allowedfiletypes'] = $inputstring;

  $baseDir = $form_state['values']['ftpgallery_gallerybasedir'];
  if( !file_exists( getcwd() . "/" . $baseDir ) ){
    form_set_error('ftpgallery_gallerybasedir', t('The given directory doesn\'t exist on the server.'));
  }
}

function _ftpgallery_formatFileTypeString($inputstring){
  $removeChars = array(".", ",", ";");
  $inputstring = str_replace($removeChars, " ", $inputstring);
  $inputstring = strtolower($inputstring);

  $inputArray = explode(" ", $inputstring);

  $inputArray = preg_grep("/^([a-z0-9]+)$/", $inputArray);

  return implode(" ", $inputArray);
}