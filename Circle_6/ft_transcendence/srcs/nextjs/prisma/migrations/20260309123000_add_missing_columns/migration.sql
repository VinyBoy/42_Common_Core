-- ============================================================
-- Migration: add_missing_columns
-- Aligns DB with current Prisma schema
-- ============================================================

-- -------------------------------------------------------
-- 1. AlterTable "User" — add all missing columns
-- -------------------------------------------------------
ALTER TABLE "User"
  ADD COLUMN IF NOT EXISTS "password"                        TEXT,
  ADD COLUMN IF NOT EXISTS "emailVerificationCode"           TEXT,
  ADD COLUMN IF NOT EXISTS "emailVerificationCodeExpires"    TIMESTAMP(3),
  ADD COLUMN IF NOT EXISTS "twoFactorEnabled"                BOOLEAN NOT NULL DEFAULT false,
  ADD COLUMN IF NOT EXISTS "twoFactorSecret"                 TEXT,
  ADD COLUMN IF NOT EXISTS "pendingEmail"                    TEXT,
  ADD COLUMN IF NOT EXISTS "deletedAt"                       TIMESTAMP(3),
  ADD COLUMN IF NOT EXISTS "recoveryToken"                   TEXT,
  ADD COLUMN IF NOT EXISTS "fileId"                          TEXT;

-- Drop legacy blob columns if they exist (replaced by File relation)
ALTER TABLE "User"
  DROP COLUMN IF EXISTS "imageBlob",
  DROP COLUMN IF EXISTS "imageMime";

-- -------------------------------------------------------
-- 2. AlterTable "Account" — add missing columns
-- -------------------------------------------------------
ALTER TABLE "Account"
  ADD COLUMN IF NOT EXISTS "providerUsername"  TEXT,
  ADD COLUMN IF NOT EXISTS "isPublic"          BOOLEAN NOT NULL DEFAULT false;

-- -------------------------------------------------------
-- 3. CreateTable "File"
-- -------------------------------------------------------
CREATE TABLE IF NOT EXISTS "File" (
  "id"        TEXT NOT NULL,
  "name"      TEXT,
  "mime"      TEXT,
  "size"      INTEGER,
  "blob"      BYTEA NOT NULL,
  "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,

  CONSTRAINT "File_pkey" PRIMARY KEY ("id")
);

-- -------------------------------------------------------
-- 4. CreateTable "Message"
-- -------------------------------------------------------
CREATE TABLE IF NOT EXISTS "Message" (
  "id"         TEXT NOT NULL,
  "content"    TEXT,
  "createdAt"  TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "updatedAt"  TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "isRead"     BOOLEAN NOT NULL DEFAULT false,
  "fileId"     TEXT,
  "senderId"   TEXT NOT NULL,
  "receiverId" TEXT NOT NULL,

  CONSTRAINT "Message_pkey" PRIMARY KEY ("id")
);

-- -------------------------------------------------------
-- 5. CreateTable "Block"
-- -------------------------------------------------------
CREATE TABLE IF NOT EXISTS "Block" (
  "id"        TEXT NOT NULL,
  "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "blockerId" TEXT NOT NULL,
  "blockedId" TEXT NOT NULL,

  CONSTRAINT "Block_pkey" PRIMARY KEY ("id")
);

-- -------------------------------------------------------
-- 6. Unique indexes
-- -------------------------------------------------------
CREATE UNIQUE INDEX IF NOT EXISTS "User_fileId_key"    ON "User"("fileId");
CREATE UNIQUE INDEX IF NOT EXISTS "Message_fileId_key" ON "Message"("fileId");
CREATE UNIQUE INDEX IF NOT EXISTS "Block_blockerId_blockedId_key" ON "Block"("blockerId", "blockedId");

-- -------------------------------------------------------
-- 7. Regular indexes
-- -------------------------------------------------------
CREATE INDEX IF NOT EXISTS "Message_senderId_receiverId_idx" ON "Message"("senderId", "receiverId");

-- -------------------------------------------------------
-- 8. Foreign keys — User.fileId -> File.id
-- -------------------------------------------------------
DO $$
BEGIN
  IF NOT EXISTS (
    SELECT 1 FROM information_schema.table_constraints
    WHERE constraint_name = 'User_fileId_fkey'
  ) THEN
    ALTER TABLE "User"
      ADD CONSTRAINT "User_fileId_fkey"
      FOREIGN KEY ("fileId") REFERENCES "File"("id")
      ON DELETE SET NULL ON UPDATE CASCADE;
  END IF;
END $$;

-- -------------------------------------------------------
-- 9. Foreign keys — Message
-- -------------------------------------------------------
DO $$
BEGIN
  IF NOT EXISTS (
    SELECT 1 FROM information_schema.table_constraints
    WHERE constraint_name = 'Message_fileId_fkey'
  ) THEN
    ALTER TABLE "Message"
      ADD CONSTRAINT "Message_fileId_fkey"
      FOREIGN KEY ("fileId") REFERENCES "File"("id")
      ON DELETE SET NULL ON UPDATE CASCADE;
  END IF;
END $$;

DO $$
BEGIN
  IF NOT EXISTS (
    SELECT 1 FROM information_schema.table_constraints
    WHERE constraint_name = 'Message_senderId_fkey'
  ) THEN
    ALTER TABLE "Message"
      ADD CONSTRAINT "Message_senderId_fkey"
      FOREIGN KEY ("senderId") REFERENCES "User"("id")
      ON DELETE CASCADE ON UPDATE CASCADE;
  END IF;
END $$;

DO $$
BEGIN
  IF NOT EXISTS (
    SELECT 1 FROM information_schema.table_constraints
    WHERE constraint_name = 'Message_receiverId_fkey'
  ) THEN
    ALTER TABLE "Message"
      ADD CONSTRAINT "Message_receiverId_fkey"
      FOREIGN KEY ("receiverId") REFERENCES "User"("id")
      ON DELETE CASCADE ON UPDATE CASCADE;
  END IF;
END $$;

-- -------------------------------------------------------
-- 10. Foreign keys — Block
-- -------------------------------------------------------
DO $$
BEGIN
  IF NOT EXISTS (
    SELECT 1 FROM information_schema.table_constraints
    WHERE constraint_name = 'Block_blockerId_fkey'
  ) THEN
    ALTER TABLE "Block"
      ADD CONSTRAINT "Block_blockerId_fkey"
      FOREIGN KEY ("blockerId") REFERENCES "User"("id")
      ON DELETE CASCADE ON UPDATE CASCADE;
  END IF;
END $$;

DO $$
BEGIN
  IF NOT EXISTS (
    SELECT 1 FROM information_schema.table_constraints
    WHERE constraint_name = 'Block_blockedId_fkey'
  ) THEN
    ALTER TABLE "Block"
      ADD CONSTRAINT "Block_blockedId_fkey"
      FOREIGN KEY ("blockedId") REFERENCES "User"("id")
      ON DELETE CASCADE ON UPDATE CASCADE;
  END IF;
END $$;
