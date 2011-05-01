<?php

// error handling
function _ftpgallery_formatError($errorText, $warning = FALSE){
  $output  = $warning ? t("Warning") : t("Error");
  $output .= ": ";
  $output .= check_plain($errorText);

  form_set_error($output, $output);
}

function theme_ftpgallery_debug($node) {
  $output = '<div class="ftpgallery_error">';
  $output .= "Debug info: <br />";

  $output .= "Thumbnail prefix: ";
  $output .= variable_get('ftpgallery_thumbprefix', 'thumb_') . "<br />";

  $output .= "Allowed file types: ";
  $output .= variable_get('ftpgallery_allowedfiletypes', 'jpg jpeg png') . "<br />";

  $output .= "Gallery path: ";
  $output .= _ftpgallery_galleryPath($node) . "<br />";

  if( count($node->gallery['thumbnails']) > 0 ){
    foreach($node->gallery['thumbnails'] as $thumbnail){
      $output .= _ftpgallery_galleryPath($node) . $thumbnail . "<br />";
    }
  }

  if( count($node->gallery['pictures']) > 0 ){
    foreach($node->gallery['pictures'] as $picture){
      $output .= _ftpgallery_galleryPath($node) . $picture . "<br />";
    }
  }
  $output .= '</div>';
  return $output;
}
