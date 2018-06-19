create database momo_word;
use momo_word;
create table word (
  wid int auto_increment not null,
  word varchar(30) not null,
  phonogram varchar(30) not null ,
  translation varchar(100) not null ,
  primary key (wid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table book (
  bid int auto_increment not null ,
  bname varchar(50) not null ,
  primary key (bid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table word_book (
  wid int not null ,
  bid int not null ,
  foreign key (wid) references word(wid),
  foreign key (bid) references book(bid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table user (
  uid int auto_increment not null ,
  uname varchar(50) not null ,
  sex bool not null ,
  daily_plan int not null ,
  english_or_chinese bool not null ,
  primary key (uid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table user_book (
  uid int not null ,
  bid int not null ,
  foreign key (uid) references user(uid),
  foreign key (bid) references book(bid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table history (
  uid int not null ,
  wid int not null ,
  `time` timestamp not null ,
  foreign key (uid) references user(uid),
  foreign key (wid) references word(wid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table memory (
  uid int not null ,
  wid int not null ,
  proficiency int not null ,
  `date` timestamp not null ,
  foreign key (uid) references user(uid),
  foreign key (wid) references word(wid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table plan (
  uid int not null ,
  wid int not null ,
  is_new bool not null ,
  `date` timestamp not null ,
  foreign key (uid) references user(uid),
  foreign key (wid) references word(wid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;
create table punch (
  uid int not null ,
  `date` timestamp not null ,
  foreign key (uid) references user(uid)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;

show tables ;

create trigger punch_trigger_insert
before insert on punch
for each row begin
  if (DATE(NEW.date) in (select DATE(date) from punch)) then
    signal sqlstate '45000'
    set message_text  = 'only one punch one day';
  end if;
end;