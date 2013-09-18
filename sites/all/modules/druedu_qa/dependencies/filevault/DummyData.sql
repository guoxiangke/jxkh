DELIMITER $$
CREATE PROCEDURE dummy_data()

BEGIN
  DECLARE i INT Default 1;
    simple_loop: LOOP
      INSERT INTO  `debug`.`filevault_files` (`id` ,`vid` ,`filename` ,`size` ,`uri` ,`fid` ,`md5` ,`mime_type` ,`uid` ,`public` ,`public_dir` ,`private_dir` ,`updated` ,`created`) VALUES ('0',  '0',  'IMG_0700.jpg', FLOOR(100000 + (RAND() * 10000000))  ,  'public://IMG_0700_5.jpg',  '132',  'Not implement yet',  'image/jpeg',  '1',  '1',  CONCAT_WS('/',FLOOR((RAND() * 1000)),FLOOR((RAND() * 100))),  CONCAT_WS('/',FLOOR((RAND() * 1000))), UNIX_TIMESTAMP() , UNIX_TIMESTAMP() );

      set i = i+1;
      IF i=1000000 THEN
        LEAVE simple_loop;
      END IF;
    END LOOP simple_loop;
END


