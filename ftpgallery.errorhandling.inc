<?php


function theme_ftpgallery_debug($node) {
  $output = '<div class="ftpgallery_error">';
  $output .= "<h2>Debug info</h2>";

  $output .= "Thumbnail prefix: ";
  $output .= $node->thumbid . "<br />";

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
