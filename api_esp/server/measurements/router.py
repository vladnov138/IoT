from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session

from database import get_db
from measurements import schemas, models

router = APIRouter(
    prefix="/data",
    tags=["data"],
    responses={404: {"description": "Not found"}},
)


@router.post("/", response_model=schemas.TemperatureValue)
def post_data(value: schemas.TemperatureValue, db: Session = Depends(get_db)):
    db_data = models.TemperatureValueModel(device_id=value.device_id, value=value.value, location=value.location)
    db.add(db_data)
    db.commit()
    db.refresh(db_data)
    return db_data


@router.get("/{location}", response_model=schemas.TemperatureValue)
def get_data(location: str, db: Session = Depends(get_db)):
    result = db.query(models.TemperatureValueModel).filter(models.TemperatureValueModel.location == location).first()
    if result is None:
        raise HTTPException(status_code=404, detail="Location not found")
    return result

