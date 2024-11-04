import os

def list_deleted_files(disk_image):
    print(f"Listing deleted files on {disk_image}:")
    
    # Use `fls` to list deleted files and get their inodes
    os.system(f"fls -r {disk_image}")

def recover_deleted_file(disk_image, inode, output_filename):
    print(f"Recovering file with inode {inode} from {disk_image}:")
    
    # Use `icat` to recover the file based on the inode number
    os.system(f"icat {disk_image} {inode} > {output_filename}")
    print(f"Recovered file saved as {output_filename}")

def forensic_file_recovery():
    # Ask for the disk image (or partition) to analyze
    disk_image = input("Enter the path to the disk image or partition (e.g., /dev/sda1 or mydisk.img): ")
    
    # Step 1: List deleted files and their inodes
    list_deleted_files(disk_image)
    
    # Step 2: Ask for the inode number of the file to recover
    inode = input("Enter the inode number of the deleted file you want to recover: ")
    
    # Step 3: Ask for the output filename to save the recovered file
    output_filename = input("Enter the name for the recovered file (e.g., recovered_file.txt): ")
    
    # Step 4: Recover the file
    recover_deleted_file(disk_image, inode, output_filename)

if __name__ == "__main__":
    forensic_file_recovery()
